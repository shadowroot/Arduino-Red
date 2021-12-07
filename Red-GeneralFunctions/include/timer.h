#include <Arduino.h>

#define MAX_TIMERS 10

template<typename T>
class Timer{
    public:
        Timer(const unsigned long& interval=0, 
                bool repeats=false, 
                T fn=nullptr): 
            lastRun(0), timeInterval(interval), repeats(repeats), fn(fn){}
        
        int run() {
            if(repeats || !lastRun){
                unsigned long now = millis();
                if((now-lastRun) >= timeInterval){
                    fn();
                    lastRun = now;
                    return true;
                }
            }
            return false;
        }

        unsigned long nextTime(){
            if(repeats || lastRun == 0){
                return millis() - lastRun;
            }
            return -1;
        }

    private:
        unsigned long lastRun;
        unsigned long timeInterval;
        bool repeats;
        T fn;
};

class AsyncTimer{
    public:
        AsyncTimer() : timers(MAX_TIMERS){}
        void loop(){
            std::vector<Timer *> newTimers;
            for(auto t = timers.begin(); t != timers.end(); ++t){
                if(t->run()){
                    auto ptr = std::lower_bound(newTimers.begin(), newTimers.end(), t);
                    newTimers.insert(ptr, t);
                }
                else{
                    newTimers.push_back(t);
                }
            }
            timers = newTimers;
        }
    protected:
       std::vector<Timer *> timers;
};