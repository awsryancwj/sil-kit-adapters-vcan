/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>,
 * Matthias Haselmaier <mhaselmaier@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_async_CoroutineWaitList_hpp
#define oatpp_async_CoroutineWaitList_hpp

#include "oatpp/core/async/Coroutine.hpp"
#include "oatpp/core/async/utils/FastQueue.hpp"

#include "oatpp/core/concurrency/SpinLock.hpp"
#include <map>
#include <mutex>
#include <thread>
#include <utility>

namespace oatpp { namespace async {

/**
 * List of &id:oatpp::async::Coroutine; waiting to be notified.
 */
class CoroutineWaitList {
  friend Processor;
public:
  /**
   * Listener for new items in the wait-list.
   */
  class Listener {
  public:
    /**
     * Default virtual destructor.
     */
    virtual ~Listener() = default;

    /**
     * Called when new item is pushed to the list.
     * @param list - list where new item was pushed to.
     */
    virtual void onNewItem(CoroutineWaitList& list) = 0;
  };
private:
  utils::FastQueue<CoroutineHandle> m_list;
  oatpp::concurrency::SpinLock m_lock;
  Listener* m_listener = nullptr;
  
  std::map<Processor*, v_int64> m_timeoutCheckingProcessors;
  std::vector<std::pair<CoroutineHandle*, v_int64>> m_coroutinesWithTimeout;
  oatpp::concurrency::SpinLock m_timeoutsLock;

private:
  void checkCoroutinesForTimeouts();

  void removeFirstCoroutine();

protected:
  /*
   * Put coroutine on wait-list.
   * This method should be called by Coroutine Processor only.
   * @param coroutine
   */
  void pushFront(CoroutineHandle* coroutine);

  /*
   * Put coroutine on wait-list with timeout.
   * This method should be called by Coroutine Processor only.
   * @param coroutine
   * @param timeoutTimeSinceEpochMS
   */
  void pushFront(CoroutineHandle* coroutine, v_int64 timeoutTimeSinceEpochMS);

  /*
   * Put coroutine on wait-list.
   * This method should be called by Coroutine Processor only.
   * @param coroutine
   */
  void pushBack(CoroutineHandle* coroutine);
  
  /*
   * Put coroutine on wait-list with timeout.
   * This method should be called by Coroutine Processor only.
   * @param coroutine
   * @param timeoutTimeSinceEpochMS
   */
  void pushBack(CoroutineHandle* coroutine, v_int64 timeoutTimeSinceEpochMS);
public:

  /**
   * Deleted copy-constructor.
   * @param other
   */
  CoroutineWaitList(const CoroutineWaitList&) = delete;
  CoroutineWaitList& operator=(const CoroutineWaitList&) = delete;

public:

  /**
   * Default constructor.
   */
  CoroutineWaitList() = default;

  /**
   * Move-constructor.
   * @param other
   */
  CoroutineWaitList(CoroutineWaitList&& other);

  /**
   * Virtual destructor.
   * Will call notifyAllAndClear().
   */
  virtual ~CoroutineWaitList();

  /**
   * Set wait list listener. <br>
   * Listener will be called when processor puts coroutine on a wait-list.
   * @param listener
   */
  void setListener(Listener* listener);

  /**
   * Put first-in-list coroutine back to its processor.
   */
  void notifyFirst();

  /**
   * Put all coroutines back to its processors and clear wait-list.
   */
  void notifyAll();

  CoroutineWaitList& operator=(CoroutineWaitList&& other);

};

}}

#endif //oatpp_async_CoroutineWaitList_hpp
