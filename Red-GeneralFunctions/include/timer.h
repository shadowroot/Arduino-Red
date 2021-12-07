#include <Arduino.h>

#define MAX_TIMERS 10

template<typename T>
class Timer{
    public:
        Timer(const unsigned long& interval=0, 
                bool repeats=false, 
                T fn=nullptr): 
            lastRun(0), timeInterval(interval), repeats(repeats), fn(fn){}
        
        void next() {
            if(lastRun == 0){
                fn();
                return;
            }
            if(repeats || lastRun == 0){
                unsigned long now = millis();
                if((now-lastRun) >= timeInterval){
                    fn();
                    lastRun = now;
                }
            }
        }

        unsigned long nextTime(){
            return millis() - lastRun;
        }

    private:
        unsigned long lastRun;
        unsigned long timeInterval;
        bool repeats;
        T fn;
};

class AsyncTimer{
    public:
        AsyncTimer(){}
        
    protected:
       Timer * timers[MAX_TIMERS]
};