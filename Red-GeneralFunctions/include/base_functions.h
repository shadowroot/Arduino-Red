#include <Arduino.h>

class Value{

};
class Capability{


};
class Capabilities{
    public:
        void add_capability(const Capability * cap);
    
};

class Event{
    public:
        Event(const RedBaseAsync * bc): baseComp(bc){}
        void call(){
            baseComp->async_hook();
        }
    protected:
        const RedBase * baseComp;
};

class SyncEvent{
    public:
        Event(): baseComps(){}
        Event(std::vector<const RedBaseSync *> bcs): baseComps(bcs){}
        void addSyncEvent(const RedBaseSync& rbs){
            baseComps.push_back(&rbs);
        }
        void call(){
            for (auto bc=baseComps.begin(); bc != baseComps.end(); ++bc){
                bc->sync_hook();
            }
        }
    protected:
        //A lot of overhead for the MCU, I know ...
        std::vector<const RedBaseSync *> baseComps;
};

class RedBase{
    public:
        void setup_hook();
        void set_property(const Capability * cap, const Value * value);
        const Capabilities * discover();
    protected:
        Capabilities capabilities;
};

class RedBaseAsync: public RedBase{
    public:
        void async_hook();
};

class RedBaseSync: public RedBase{
    public:
        void sync_hook();
};