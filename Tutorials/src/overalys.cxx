#include <vector>
#include "Framework/AnalysisDataModel.h"
#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Common/DataModel/EventSelection.h"
#include "Common/DataModel/Centrality.h"
#include "Common/DataModel/Multiplicity.h"
#include "Framework/Helpers.h"
#include "Framework/Overlays.h"
#include "Framework/BuketPolicy.h"

using namespace o2;
using namespace o2::framework;
using namespace o2::framework::expressions;
using namespace o2::soa;
 
struct FirstTest {
  SliceCache cache;
  Preslice<aod::Tracks> perCollision = aod::track::collisionId;
  std::vector<double> xBins{-0.064, -0.062, -0.060, 0.066, 0.068, 0.070, 0.072};
  std::vector<double> yBins{-0.320, -0.301, -0.300, 0.330, 0.340, 0.350, 0.360};
  using BinningType = ColumnBinningPolicy2<aod::collision::PosX, aod::collision::PosY>;
  BinningType bp{{xBins, yBins}, true};                                            
       
  void process(aod::Collisions const& collisions, aod::Tracks const& tracks) {
    auto begin = collisions.begin();
    auto tmp = collisions.end();
    auto end = begin + tmp.index;
    auto res = groupData(begin, end, bp);   
  }
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
   return WorkflowSpec{
     adaptAnalysisTask<FirstTest>(cfgc), 
   };
}

