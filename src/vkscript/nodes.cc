// Copyright 2018 The Amber Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/vkscript/nodes.h"

#include <cassert>
#include <utility>

namespace amber {
namespace vkscript {

Node::Node(NodeType type) : node_type_(type) {}

Node::~Node() = default;

IndicesNode* Node::AsIndices() {
  return static_cast<IndicesNode*>(this);
}

RequireNode* Node::AsRequire() {
  return static_cast<RequireNode*>(this);
}

VertexDataNode* Node::AsVertexData() {
  return static_cast<VertexDataNode*>(this);
}

RequireNode::RequireNode() : Node(NodeType::kRequire) {}

RequireNode::~RequireNode() = default;

RequireNode::Requirement::Requirement(Feature feature) : feature_(feature) {}

RequireNode::Requirement::Requirement(Feature feature,
                                      std::unique_ptr<Format> format)
    : feature_(feature), format_(std::move(format)) {}

RequireNode::Requirement::Requirement(Requirement&&) = default;

RequireNode::Requirement::~Requirement() = default;

void RequireNode::AddRequirement(Feature feature,
                                 std::unique_ptr<Format> format) {
  requirements_.emplace_back(feature, std::move(format));
}

IndicesNode::IndicesNode(std::unique_ptr<Buffer> buffer)
    : Node(NodeType::kIndices), buffer_(std::move(buffer)) {}

IndicesNode::~IndicesNode() = default;

VertexDataNode::VertexDataNode() : Node(NodeType::kVertexData) {}

VertexDataNode::~VertexDataNode() = default;

void VertexDataNode::SetSegment(Header&& header, std::vector<Value>&& data) {
  data_.push_back({std::move(header), std::move(data)});
}

}  // namespace vkscript
}  // namespace amber
