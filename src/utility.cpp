//
//  utility.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/30.
//
//

#include "utility.hpp"

SparseExecutor::SparseExecutor
(int _mod,
 std::function<void()> _fn)
:mod(_mod),fn(_fn),count(0)
{
}

void SparseExecutor::touch(){
  ++count;
  if(count == mod){
    fn();
    count = 0;
  }
}
