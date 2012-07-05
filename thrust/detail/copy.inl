/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include <thrust/detail/config.h>
#include <thrust/detail/copy.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/copy.h>
#include <thrust/system/detail/adl/copy.h>

namespace thrust
{


template<typename System, typename InputIterator, typename OutputIterator>
  OutputIterator copy(thrust::detail::dispatchable_base<System> &system,
                      InputIterator first,
                      InputIterator last,
                      OutputIterator result)
{
  using thrust::system::detail::generic::copy;
  return copy(system.derived(), first, last, result);
} // end copy()


template<typename System, typename InputIterator, typename Size, typename OutputIterator>
  OutputIterator copy_n(thrust::detail::dispatchable_base<System> &system,
                        InputIterator first,
                        Size n,
                        OutputIterator result)
{
  using thrust::system::detail::generic::copy_n;
  return copy_n(system.derived(), first, n, result);
} // end copy_n()


namespace detail
{


template<typename System, typename InputIterator, typename OutputIterator>
  OutputIterator strip_const_copy(const System &system,
                                  InputIterator first,
                                  InputIterator last,
                                  OutputIterator result)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::copy(non_const_system, first, last, result);
} // end copy()

template<typename System, typename InputIterator, typename Size, typename OutputIterator>
  OutputIterator strip_const_copy_n(const System &system,
                                    InputIterator first,
                                    Size n,
                                    OutputIterator result)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::copy_n(non_const_system, first, n, result);
} // end copy_n()


} // end detail


template<typename InputIterator,
         typename OutputIterator>
  OutputIterator copy(InputIterator first,
                      InputIterator last,
                      OutputIterator result)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type  system1;
  typedef typename thrust::iterator_system<OutputIterator>::type system2;

  return thrust::detail::strip_const_copy(select_system(system1(),system2()), first, last, result);
} // end copy()


template<typename InputIterator,
         typename Size,
         typename OutputIterator>
  OutputIterator copy_n(InputIterator first,
                        Size n,
                        OutputIterator result)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type  system1;
  typedef typename thrust::iterator_system<OutputIterator>::type system2;

  return thrust::detail::strip_const_copy_n(select_system(system1(),system2()), first, n, result);
} // end copy_n()


} // end namespace thrust

