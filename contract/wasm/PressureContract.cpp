#include <platon/platon.hpp>
#include <string>
using namespace std;
using namespace platon;

CONTRACT PressureContract : public platon::Contract {
 public:
  ACTION void init(const uint64_t &BeginBlock, const uint64_t &EndBlock) {
    begin_block.self() = BeginBlock;
    end_block.self() = EndBlock;
    owner.self() = platon_caller();
  }

  ACTION void setBeginAndEndBlock(const uint64_t &BeginBlock,
                                  const uint64_t &EndBlock) {
    if (owner.self() == platon_caller()) {
      begin_block.self() = BeginBlock;
      end_block.self() = EndBlock;
    }
  }

  ACTION void record(std::string & nodeID) {
    uint64_t currentblcok = platon_block_number();
    if (currentblcok >= begin_block.self() &&
        currentblcok <= end_block.self()) {
      u128 v = 0;
      if (get_state(nodeID, v) != 0) {
        set_state(nodeID, v + 1);
      } else {
        v = 1;
        set_state(nodeID, v);
        addNodeId(nodeID);
      }
    }
  }

  ACTION void clearMap() {
    if (owner.self() == platon_caller()) {
      clearNodeIds();
    }
  }

  CONST u128 getValue(std::string & nodeID) {
    u128 v = 0;
    get_state(nodeID, v);
    return v;
  }

 private:
  void addNodeId(const std::string &nodeID) {
    vector<std::string> nodeIds;
    get_state("nodeidlist", nodeIds);
    nodeIds.push_back(nodeID);
    set_state("nodeidlist", nodeIds);
  }

  void clearNodeIds() {
    vector<std::string> nodeIds;
    get_state("nodeidlist", nodeIds);
    for (const std::string &n : nodeIds) {
      del_state(n);
    }
  }

 private:
  platon::StorageType<"owner"_n, Address> owner;
  platon::StorageType<"beginblock"_n, uint64_t> begin_block;
  platon::StorageType<"endblock"_n, uint64_t> end_block;
};

PLATON_DISPATCH(PressureContract,
                (init)(setBeginAndEndBlock)(record)(clearMap)(getValue))
