/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_COMMON_RUNTIME_GPU_GPU_ID_H_
#define TENSORFLOW_CORE_COMMON_RUNTIME_GPU_GPU_ID_H_

#include "tensorflow/core/lib/gtl/int_type.h"

namespace tensorflow {

// There are three types of GPU ids:
// - *physical* GPU id: this is the integer index of a GPU hardware in the
//   physical machine, it can be filtered by CUDA environment variable
//   CUDA_VISIBLE_DEVICES. Note that this id is not visible to Tensorflow, but
//   result after filtering by CUDA_VISIBLE_DEVICES is visible to TF and is
//   called CUDA GPU id as below. See
//   http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#env-vars
//   for more details.
// - CUDA GPU id (also called *visible* GPU id in
//   third_party/tensorflow/core/protobuf/config.proto): this is the id that is
//   visible to Tensorflow after filtering by CUDA_VISIBLE_DEVICES, and is
//   generated by the CUDA GPU driver. It starts from 0 and is used for CUDA API
//   calls like cuDeviceGet().
// - TF GPU id (also called *virtual* GPU id in
//   third_party/tensorflow/core/protobuf/config.proto): this is the id that
//   Tensorflow generates and exposes to its users. It is the id in the <id>
//   field of the device name "/device:GPU:<id>", and is also the identifier of
//   a BaseGPUDevice. Note that the configuration allows us to create multiple
//   BaseGPUDevice per GPU hardware in order to use multi CUDA streams on the
//   hardware, so the mapping between TF GPU id and CUDA GPU id is not a 1:1
//   mapping, see the example below.
//
// For example, assuming that in the machine we have GPU device with index 0, 1,
// 2 and 3 (physical GPU id). Setting "CUDA_VISIBLE_DEVICES=1,2,3" will create
// the following mapping between CUDA GPU id and physical GPU id:
//
//        CUDA GPU id ->  physical GPU id
//                 0  ->  1
//                 1  ->  2
//                 2  ->  3
//
// Note that physical GPU id 0 is invisible to TF so there is no mapping entry
// for it.
//
// Assuming we configure the Session to create one BaseGPUDevice per GPU
// hardware, then setting GPUOptions::visible_device_list to "2,0" will create
// the following mappting between TF GPU id and CUDA GPU id:
//
//                  TF GPU id  ->  CUDA GPU ID
//      0 (i.e. /device:GPU:0) ->  2
//      1 (i.e. /device:GPU:1) ->  0
//
// Note that CUDA GPU id 1 is filtered out by GPUOptions::visible_device_list,
// so it won't be used by the TF process.
//
// On the other hand, if we configure it to create 2 BaseGPUDevice per GPU
// hardware, then setting GPUOptions::visible_device_list to "2,0" will create
// the following mappting between TF GPU id and CUDA GPU id:
//
//                  TF GPU id  ->  CUDA GPU ID
//      0 (i.e. /device:GPU:0) ->  2
//      1 (i.e. /device:GPU:1) ->  2
//      2 (i.e. /device:GPU:2) ->  0
//      3 (i.e. /device:GPU:3) ->  0
//
// We create strong-typed integer classes for both TF GPU id and CUDA GPU id to
// minimize programming errors and improve code readability. Except for the
// StreamExecutor interface (as we don't change its API), whenever we need a
// TF GPU id (or CUDA GPU id) we should use TfGpuId (or CudaGpuId) instead of a
// raw integer.
TF_LIB_GTL_DEFINE_INT_TYPE(TfGpuId, int32);
TF_LIB_GTL_DEFINE_INT_TYPE(CudaGpuId, int32);

}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_COMMON_RUNTIME_GPU_GPU_ID_H_
