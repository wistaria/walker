/*
   Copyright (C) 2022 by Synge Todo <wistaria@phys.s.u-tokyo.ac.jp>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once
#include <algorithm>
#include <vector>

namespace walker {

template<class IntType = int> 
class tower_sampling {
public:
  typedef IntType result_type;
  tower_sampling() : sum_(1.0), table_(1, 1.0) {}
  template <class InputIterator>
  tower_sampling(InputIterator firstW, InputIterator lastW) : table_(0) {
    sum_ = std::accumulate(firstW, lastW, 0.0);
    double s = 0.0;
    for (auto itr = firstW; itr != lastW; ++itr) {
      s += *itr;
      table_.push_back(s / sum_);
    }
  }
  template<class Engine>
  result_type operator()(Engine& eng) const {
    auto itr = std::upper_bound(table_.begin(), table_.end(), dist_(eng));
    return result_type(itr - table_.begin());
  }
private:
  mutable std::uniform_real_distribution<> dist_;
  double sum_;
  std::vector<double> table_;
};

}
