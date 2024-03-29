#include <dcd/dcd.hpp>
#include <dcd/system.hpp>
#include <dcd/table.hpp>
using namespace dcd;

struct todo_entry {
  std::string uuid;
  std::tuple<dcd::name, std::string> account_name;
  std::tuple<std::string, std::string> task;
  std::tuple<bool, std::string> checked;
  std::tuple<uint32_t, std::string> created;

  std::string get_uuid() const { return uuid; }
  dcd::name get_account_name() const { return std::get<0>(account_name); }
  std::string get_task() const { return std::get<0>(task); }
  bool get_checked() const { return std::get<0>(checked); }
  int get_created() const { return std::get<0>(created); }
};

class [[dcd::contract]] kv_todo : public contract {
  struct [[dcd::table]] todo_table : dcd::kv::table<todo_entry, "todo"_n> {
    KV_NAMED_INDEX("uuid"_n, uuid);
    KV_NAMED_INDEX("accname"_n, account_name);
    KV_NAMED_INDEX("task"_n, task)
    KV_NAMED_INDEX("checked"_n, checked)
    KV_NAMED_INDEX("created"_n, created)

    // constructor for our `kvtodo` table to setup and initialize it
    todo_table(dcd::name contract_name) { init(contract_name, uuid, account_name, task, checked, created); }
  };
  public:
      using contract::contract;

      [[dcd::action]]
      std::vector<todo_entry> getbyaccname(name account_name);

      [[dcd::action]]
      size_t cntbyaccname(name account_name);

      [[dcd::action]]
      std::vector<todo_entry> getbytask(std::string task);

      [[dcd::action]]
      size_t cntbytask(std::string name);

      [[dcd::action]]
      std::vector<todo_entry> getbychecked(bool value);

      [[dcd::action]]
      size_t cntbychecked(bool checked);

      [[dcd::action]]
      todo_entry upsert(const std::string& uuid,
                        dcd::name account_name,
                        const std::string& task,
                        bool checked);

      [[dcd::action]]
      void del(const std::string& uuid);

      using get_by_account_name_action = action_wrapper<"getbyaccname"_n, &kv_todo::getbyaccname>;
      using cnt_by_account_name_action = action_wrapper<"cntbyaccname"_n, &kv_todo::cntbyaccname>;
      using get_by_task_action = action_wrapper<"getbytask"_n, &kv_todo::getbytask>;
      using cnt_by_task_action = action_wrapper<"cntbytask"_n, &kv_todo::cntbytask>;
      using get_by_checked_action = action_wrapper<"getbychecked"_n, &kv_todo::getbychecked>;
      using cnt_by_checked_action = action_wrapper<"cntbychecked"_n, &kv_todo::cntbychecked>;

      using upsert_action = action_wrapper<"upsert"_n, &kv_todo::upsert>;
      using del_action = action_wrapper<"del"_n, &kv_todo::del>;

  private:
    todo_table todo_entries{"todo"_n};
};
