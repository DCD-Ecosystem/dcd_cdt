#include <dcd/dcd.hpp>
#include <dcd/asset.hpp>
#include <dcd/table.hpp>

extern "C" __attribute__((dcd_wasm_import)) void set_kv_parameters_packed(const void* params, uint32_t size);

using namespace dcd;

struct kvtest_record {
    std::string id;
    std::string data;
};

class [[dcd::contract]] kvtest : public contract {
    struct [[dcd::table]] kvtest_table : dcd::kv::table<kvtest_record, "dcd"_n> {
        KV_NAMED_INDEX("by.id", id);
        kvtest_table(name contract) { init(contract, id); }
    };

    public:
        using contract::contract;

        kvtest(dcd::name receiver, dcd::name code, dcd::datastream<const char *> ds) :
	        contract(receiver, code, ds)
        {
            uint32_t limits[4];
            limits[0] = 0;
            limits[1] = 1024 * 1024;
            limits[2] = 9 * 1024 * 1024;
            limits[3] = 10;
            set_kv_parameters_packed(limits, sizeof(limits));
        }

        [[dcd::action]]
        void smalltest() {
            require_auth(_self);
            kvtest_table table{"dcd"_n};

            uint64_t id = 1;
            std::string data = "test";
        
            for (; id < 5000; ++id) {
                table.put({std::to_string(id), data + std::to_string(id)}, get_self());
            }
        	
            for (id = 1; id < 5000; ++id) {
                auto itr = table. id.find(std::to_string(id));
                if (itr != table.id.end()) {
                    std::string val = itr.value().data;
                    dcd::check(val.compare(data + std::to_string(id)) == 0, "The value for the key " + std::to_string(id) + " is " + val);
        	}
            }
        }

        [[dcd::action]]
        void largetest() {
            require_auth(_self);

            kvtest_table table{"dcd"_n};
            
            std::string data = std::string(8 * 1024 * 1024, 't');

            uint64_t id = 1;
            for (; id < 200; ++id)
                table.put({std::to_string(id), std::to_string(id) + data}, get_self());
        	    
            for (id = 1; id < 200; ++id) {
                auto itr = table.id.find(std::to_string(id));
                if (itr != table.id.end()) {
                    std::string val = itr.value().data.substr(0, 10);
                    std::string expected = (std::to_string(id) + data).substr(0, 10);
                    dcd::check(val.compare(expected) == 0, "The value for the key " + std::to_string(id) + " is " + val + "...");
                }
            }
        }
};
