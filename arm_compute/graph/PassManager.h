/*
 * Copyright (c) 2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ARM_COMPUTE_GRAPH_PASSMANAGER_H__
#define __ARM_COMPUTE_GRAPH_PASSMANAGER_H__

#include "arm_compute/graph/IGraphMutator.h"

#include <memory>
#include <vector>

namespace arm_compute
{
namespace graph
{
// Forward declarations
class Graph;

/** Pass manager
 *
 * Responsible for performing the mutating graph passes with a given order
 **/
class PassManager final
{
public:
    /** Constructor */
    PassManager();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    PassManager(const PassManager &) = delete;
    /** Default move constructor */
    PassManager(PassManager &&) = default;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    PassManager &operator=(const PassManager &) = delete;
    /** Default move assignment operator */
    PassManager &operator=(PassManager &&) = default;
    /** Mutation passes accessors
     *
     * @return Returns the vector with the mutation passes that are to be executed on a graph
     */
    const std::vector<std::unique_ptr<IGraphMutator>> &passes() const;
    /** Accessor of a pass at a given index
     *
     * @param[in] index Index of the requested pass
     *
     * @return A pointer to the given pass if exists else nullptr
     */
    IGraphMutator *pass(size_t index);
    /** Appends a mutation pass
     *
     * @param[in] pass Pass to append
     */
    void append(std::unique_ptr<IGraphMutator> pass);
    /** Clears all the passes */
    void clear();
    /** Runs all the mutation passes on a given graph
     *
     * @param[in] g Graph to run the mutations on
     */
    void run_all(Graph &g);
    /** Runs a specific mutation pass on a given graph
     *
     * @param[in] g     Graph to run the mutation on
     * @param[in] index Index of the mutation to execute
     */
    void run(Graph &g, size_t index);

private:
    std::vector<std::unique_ptr<IGraphMutator>> _passes; /**< Vector of graph passes */
};
} // namespace graph
} // namespace arm_compute
#endif /* __ARM_COMPUTE_GRAPH_PASSMANAGER_H__ */
