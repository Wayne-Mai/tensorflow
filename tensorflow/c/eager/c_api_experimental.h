/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_C_EAGER_C_API_EXPERIMENTAL_H_
#define TENSORFLOW_C_EAGER_C_API_EXPERIMENTAL_H_

#include "tensorflow/c/c_api.h"
#include "tensorflow/c/eager/c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// Resets `op_to_reset` with `op_or_function_name` and `raw_device_name`. This
// is for performance optimization by reusing an exiting unused op rather than
// creating a new op every time. If `raw_device_name` is `NULL` or empty, it
// does not set the device name. If it's not `NULL`, then it attempts to parse
// and set the device name. It's effectively `TFE_OpSetDevice`, but it is faster
// than separately calling it because if the existing op has the same
// `raw_device_name`, it skips parsing and just leave as it is.
TF_CAPI_EXPORT extern void TFE_OpReset(TFE_Op* op_to_reset,
                                       const char* op_or_function_name,
                                       const char* raw_device_name,
                                       TF_Status* status);

TF_CAPI_EXPORT extern void TFE_OpConsumeInput(TFE_Op* op, TFE_TensorHandle* h,
                                              TF_Status* status);

// Enables only graph collection in RunMetadata on the functions executed from
// this context.
TF_CAPI_EXPORT extern void TFE_ContextEnableGraphCollection(TFE_Context* ctx);

// Disables only graph collection in RunMetadata on the functions executed from
// this context.
TF_CAPI_EXPORT extern void TFE_ContextDisableGraphCollection(TFE_Context* ctx);

// TODO(fishx): Move these monitoring APIs into a separate file.
// -----------------------------------------------------------------------------
// Monitoring Counter APIs.
// These APIs de-templated monitoring Counter for swig.

typedef struct TFE_MonitoringCounterCell TFE_MonitoringCounterCell;

// Atomically increments the value of the cell. The value must be non-negative.
TF_CAPI_EXPORT extern void TFE_MonitoringCounterCellIncrementBy(
    TFE_MonitoringCounterCell* cell, int64_t value);

// Retrieves the current value of the cell.
TF_CAPI_EXPORT extern int64_t TFE_MonitoringCounterCellValue(
    TFE_MonitoringCounterCell* cell);

// APIs for Counter without label.
typedef struct TFE_MonitoringCounter0 TFE_MonitoringCounter0;
// Returns a new Counter metric object. The caller should manage lifetime of
// the object. Using duplicate metric name will crash the program with fatal
// error.
TF_CAPI_EXPORT extern TFE_MonitoringCounter0* TFE_MonitoringNewCounter0(
    const char* name, TF_Status* status, const char* description);
// Deletes the Counter object.
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteCounter0(
    TFE_MonitoringCounter0* counter);
// Retrieves the cell from the Counter object. The Counter object will manage
// lifetime of the cell.
TF_CAPI_EXPORT extern TFE_MonitoringCounterCell* TFE_MonitoringGetCellCounter0(
    TFE_MonitoringCounter0* counter);

// APIs for Counter with 1 label.
typedef struct TFE_MonitoringCounter1 TFE_MonitoringCounter1;
TF_CAPI_EXPORT extern TFE_MonitoringCounter1* TFE_MonitoringNewCounter1(
    const char* name, TF_Status* status, const char* description,
    const char* label1);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteCounter1(
    TFE_MonitoringCounter1* counter);
TF_CAPI_EXPORT extern TFE_MonitoringCounterCell* TFE_MonitoringGetCellCounter1(
    TFE_MonitoringCounter1* counter, const char* label1);

// APIs for Counter with 2 labels.
typedef struct TFE_MonitoringCounter2 TFE_MonitoringCounter2;
TF_CAPI_EXPORT extern TFE_MonitoringCounter2* TFE_MonitoringNewCounter2(
    const char* name, TF_Status* status, const char* description,
    const char* label1, const char* label2);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteCounter2(
    TFE_MonitoringCounter2* counter);
TF_CAPI_EXPORT extern TFE_MonitoringCounterCell* TFE_MonitoringGetCellCounter2(
    TFE_MonitoringCounter2* counter, const char* label1, const char* label2);

// -----------------------------------------------------------------------------
// Monitoring Gauge APIs.
// These APIs de-templated monitoring Gauge for swig.

typedef struct TFE_MonitoringIntGaugeCell TFE_MonitoringIntGaugeCell;

// Atomically set the value of the cell.
TF_CAPI_EXPORT extern void TFE_MonitoringIntGaugeCellSet(
    TFE_MonitoringIntGaugeCell* cell, int64_t value);

// Retrieves the current value of the cell.
TF_CAPI_EXPORT extern int64_t TFE_MonitoringIntGaugeCellValue(
    TFE_MonitoringIntGaugeCell* cell);

// APIs for Int Gauge without label.
typedef struct TFE_MonitoringIntGauge0 TFE_MonitoringIntGauge0;
TF_CAPI_EXPORT extern TFE_MonitoringIntGauge0* TFE_MonitoringNewIntGauge0(
    const char* name, TF_Status* out_status, const char* description);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteIntGauge0(
    TFE_MonitoringIntGauge0* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringIntGaugeCell*
TFE_MonitoringGetCellIntGauge0(TFE_MonitoringIntGauge0* gauge);

// APIs for Int Gauge with 1 label.
typedef struct TFE_MonitoringIntGauge1 TFE_MonitoringIntGauge1;
TF_CAPI_EXPORT extern TFE_MonitoringIntGauge1* TFE_MonitoringNewIntGauge1(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteIntGauge1(
    TFE_MonitoringIntGauge1* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringIntGaugeCell*
TFE_MonitoringGetCellIntGauge1(TFE_MonitoringIntGauge1* gauge,
                               const char* label1);

// APIs for Int Gauge with 2 label.
typedef struct TFE_MonitoringIntGauge2 TFE_MonitoringIntGauge2;
TF_CAPI_EXPORT extern TFE_MonitoringIntGauge2* TFE_MonitoringNewIntGauge2(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1, const char* label2);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteIntGauge2(
    TFE_MonitoringIntGauge2* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringIntGaugeCell*
TFE_MonitoringGetCellIntGauge2(TFE_MonitoringIntGauge2* gauge,
                               const char* label1, const char* label2);

typedef struct TFE_MonitoringStringGaugeCell TFE_MonitoringStringGaugeCell;
TF_CAPI_EXPORT extern void TFE_MonitoringStringGaugeCellSet(
    TFE_MonitoringStringGaugeCell* cell, const char* value);
// Retrieves the string value and saves it in buffer.
TF_CAPI_EXPORT extern const void TFE_MonitoringStringGaugeCellValue(
    TFE_MonitoringStringGaugeCell* cell, TF_Buffer* buf);

// APIs for String Gauge without label.
typedef struct TFE_MonitoringStringGauge0 TFE_MonitoringStringGauge0;
TF_CAPI_EXPORT extern TFE_MonitoringStringGauge0* TFE_MonitoringNewStringGauge0(
    const char* name, TF_Status* out_status, const char* description);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteStringGauge0(
    TFE_MonitoringStringGauge0* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringStringGaugeCell*
TFE_MonitoringGetCellStringGauge0(TFE_MonitoringStringGauge0* gauge);

// APIs for String Gauge with 1 label.
typedef struct TFE_MonitoringStringGauge1 TFE_MonitoringStringGauge1;
TF_CAPI_EXPORT extern TFE_MonitoringStringGauge1* TFE_MonitoringNewStringGauge1(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteStringGauge1(
    TFE_MonitoringStringGauge1* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringStringGaugeCell*
TFE_MonitoringGetCellStringGauge1(TFE_MonitoringStringGauge1* gauge,
                                  const char* label1);

// APIs for String Gauge with 2 label.
typedef struct TFE_MonitoringStringGauge2 TFE_MonitoringStringGauge2;
TF_CAPI_EXPORT extern TFE_MonitoringStringGauge2* TFE_MonitoringNewStringGauge2(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1, const char* label2);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteStringGauge2(
    TFE_MonitoringStringGauge2* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringStringGaugeCell*
TFE_MonitoringGetCellStringGauge2(TFE_MonitoringStringGauge2* gauge,
                                  const char* label1, const char* label2);

typedef struct TFE_MonitoringBoolGaugeCell TFE_MonitoringBoolGaugeCell;
TF_CAPI_EXPORT extern void TFE_MonitoringBoolGaugeCellSet(
    TFE_MonitoringBoolGaugeCell* cell, bool value);
TF_CAPI_EXPORT extern bool TFE_MonitoringBoolGaugeCellValue(
    TFE_MonitoringBoolGaugeCell* cell);

// APIs for Bool Gauge without label.
typedef struct TFE_MonitoringBoolGauge0 TFE_MonitoringBoolGauge0;
TF_CAPI_EXPORT extern TFE_MonitoringBoolGauge0* TFE_MonitoringNewBoolGauge0(
    const char* name, TF_Status* out_status, const char* description);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteBoolGauge0(
    TFE_MonitoringBoolGauge0* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringBoolGaugeCell*
TFE_MonitoringGetCellBoolGauge0(TFE_MonitoringBoolGauge0* gauge);

// APIs for Bool Gauge with 1 label.
typedef struct TFE_MonitoringBoolGauge1 TFE_MonitoringBoolGauge1;
TF_CAPI_EXPORT extern TFE_MonitoringBoolGauge1* TFE_MonitoringNewBoolGauge1(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteBoolGauge1(
    TFE_MonitoringBoolGauge1* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringBoolGaugeCell*
TFE_MonitoringGetCellBoolGauge1(TFE_MonitoringBoolGauge1* gauge,
                                const char* label1);

// APIs for Bool Gauge with 2 label.
typedef struct TFE_MonitoringBoolGauge2 TFE_MonitoringBoolGauge2;
TF_CAPI_EXPORT extern TFE_MonitoringBoolGauge2* TFE_MonitoringNewBoolGauge2(
    const char* name, TF_Status* out_status, const char* description,
    const char* label1, const char* label2);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteBoolGauge2(
    TFE_MonitoringBoolGauge2* gauge);
TF_CAPI_EXPORT extern TFE_MonitoringBoolGaugeCell*
TFE_MonitoringGetCellBoolGauge2(TFE_MonitoringBoolGauge2* gauge,
                                const char* label1, const char* label2);

// -----------------------------------------------------------------------------
// Monitoring Sampler APIs.
// These APIs de-templated monitoring Sampler for swig.

typedef struct TFE_MonitoringSamplerCell TFE_MonitoringSamplerCell;

// Atomically add the value of the cell.
TF_CAPI_EXPORT extern void TFE_MonitoringSamplerCellAdd(
    TFE_MonitoringSamplerCell* cell, double value);

// Retrieves the current value of the cell. The return value is a HistogramProto
// saved in buffer.
TF_CAPI_EXPORT extern void TFE_MonitoringSamplerCellValue(
    TFE_MonitoringSamplerCell* cell, TF_Buffer* buf);

// APIs for sampler buckets
typedef struct TFE_MonitoringBuckets TFE_MonitoringBuckets;
TF_CAPI_EXPORT extern TFE_MonitoringBuckets*
TFE_MonitoringNewExponentialBuckets(double scale, double growth_factor,
                                    int bucket_count);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteBuckets(
    TFE_MonitoringBuckets* buckets);

// APIs for Sampler without label.
typedef struct TFE_MonitoringSampler0 TFE_MonitoringSampler0;
TF_CAPI_EXPORT extern TFE_MonitoringSampler0* TFE_MonitoringNewSampler0(
    const char* name, TFE_MonitoringBuckets* buckets, TF_Status* out_status,
    const char* description);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteSampler0(
    TFE_MonitoringSampler0* sampler);
TF_CAPI_EXPORT extern TFE_MonitoringSamplerCell* TFE_MonitoringGetCellSampler0(
    TFE_MonitoringSampler0* sampler);

// APIs for Sampler with 1 label.
typedef struct TFE_MonitoringSampler1 TFE_MonitoringSampler1;
TF_CAPI_EXPORT extern TFE_MonitoringSampler1* TFE_MonitoringNewSampler1(
    const char* name, TFE_MonitoringBuckets* buckets, TF_Status* out_status,
    const char* description, const char* label1);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteSampler1(
    TFE_MonitoringSampler1* sampler);
TF_CAPI_EXPORT extern TFE_MonitoringSamplerCell* TFE_MonitoringGetCellSampler1(
    TFE_MonitoringSampler1* sampler, const char* label1);

// APIs for Sampler with 2 label.
typedef struct TFE_MonitoringSampler2 TFE_MonitoringSampler2;
TF_CAPI_EXPORT extern TFE_MonitoringSampler2* TFE_MonitoringNewSampler2(
    const char* name, TFE_MonitoringBuckets* buckets, TF_Status* out_status,
    const char* description, const char* label1, const char* label2);
TF_CAPI_EXPORT extern void TFE_MonitoringDeleteSampler2(
    TFE_MonitoringSampler2* sampler);
TF_CAPI_EXPORT extern TFE_MonitoringSamplerCell* TFE_MonitoringGetCellSampler2(
    TFE_MonitoringSampler2* sampler, const char* label1, const char* label2);

// LINT.IfChange
// Note: Keep in sync with internal copy of enum in eager/context.h.
typedef enum TFE_ContextMirroringPolicy {
  // Do not maintain mirrors in a TensorHandle, instead make new TensorHandle
  // copies with their own lifetime.
  TFE_MIRRORING_NONE = 0,
  // Mirroring any remote tensor handles, associating them with the lifetime of
  // the local TensorHandle.
  TFE_MIRRORING_ALL = 1,
} TFE_ContextMirroringPolicy;
// LINT.ThenChange(//tensorflow/core/common_runtime/eager/context.h)

TF_CAPI_EXPORT extern void TFE_ContextOptionsSetMirroringPolicy(
    TFE_ContextOptions*, TFE_ContextMirroringPolicy);

// Sets a thread-local mirroring policy. After this call, other calls to
// TFE_Execute in the same thread will use the mirroring policy specified here
// instead of the mirroring policy used to construct the context. This has no
// effect on the mirroring policy used by other program threads.
TF_CAPI_EXPORT extern void TFE_ContextSetThreadLocalMirroringPolicy(
    TFE_Context*, TFE_ContextMirroringPolicy);

// Returns the mirroring policy to be used by this context in the current
// thread.
TF_CAPI_EXPORT extern TFE_ContextMirroringPolicy TFE_ContextGetMirroringPolicy(
    TFE_Context*);

// Sets whether to copy the remote inputs of a function lazily.
TF_CAPI_EXPORT extern void TFE_ContextOptionsSetLazyRemoteInputsCopy(
    TFE_ContextOptions*, bool lazy_copy);

// -----------------------------------------------------------------------------
// Cancellation APIs.

typedef struct TFE_CancellationManager TFE_CancellationManager;
TF_CAPI_EXPORT extern TFE_CancellationManager* TFE_NewCancellationManager();
TF_CAPI_EXPORT extern bool TFE_CancellationManagerIsCancelled(
    TFE_CancellationManager*);
TF_CAPI_EXPORT extern void TFE_CancellationManagerStartCancel(
    TFE_CancellationManager*);
TF_CAPI_EXPORT extern void TFE_DeleteCancellationManager(
    TFE_CancellationManager*);

// Associates the given `cancellation_manager` with `op`, so that invoking
// `TFE_CancellationManagerStartCancel(cancellation_manager)` will cancel the
// execution of `op`.
typedef struct TFE_CancellationManager TFE_CancellationManager;
TF_CAPI_EXPORT extern void TFE_OpSetCancellationManager(
    TFE_Op* op, TFE_CancellationManager* cancellation_manager,
    TF_Status* status);

// -----------------------------------------------------------------------------
// Eager Executor APIs.
typedef struct TFE_Executor TFE_Executor;

// Creates a new eager Executor. Nodes in one executor are guaranteed to be
// executed in sequence. Assigning nodes to different executors allows executing
// nodes in parallel.
TF_CAPI_EXPORT extern TFE_Executor* TFE_NewExecutor(bool is_async);

// Deletes the eager Executor without waiting for enqueued nodes. Please call
// TFE_ExecutorWaitForAllPendingNodes before calling this API if you want to
// make sure all nodes are finished.
TF_CAPI_EXPORT extern void TFE_DeleteExecutor(TFE_Executor*);

// Returns true if the executor is in async mode.
TF_CAPI_EXPORT extern bool TFE_ExecutorIsAsync(TFE_Executor*);

// Causes the calling thread to block till all ops dispatched in this executor
// have been executed. Note that "execution" here refers to kernel execution /
// scheduling of copies, etc. Similar to sync execution, it doesn't guarantee
// that lower level device queues (like GPU streams) have been flushed.
//
// This call may not block for execution of ops enqueued concurrently with this
// call.
TF_CAPI_EXPORT extern void TFE_ExecutorWaitForAllPendingNodes(
    TFE_Executor*, TF_Status* status);

// When an error happens, any pending operations are discarded and newly issued
// ops return an error. This call clears the error state and re-enables
// execution of newly issued ops.
//
// Note that outputs of discarded ops remain in a corrupt state and should not
// be used for future calls.
// TODO(agarwal): mark the affected handles and raise errors if they are used.
TF_CAPI_EXPORT extern void TFE_ExecutorClearError(TFE_Executor*);

// Sets a custom Executor for current thread. All nodes created by this thread
// will be added to this Executor. It will override current executor.
TF_CAPI_EXPORT extern void TFE_ContextSetExecutorForThread(TFE_Context*,
                                                           TFE_Executor*);

// Returns the Executor for current thread.
TF_CAPI_EXPORT extern TFE_Executor* TFE_ContextGetExecutorForThread(
    TFE_Context*);

// -----------------------------------------------------------------------------
// Dynamic cluster API.

// Update an existing context with a new set of servers defined in a ServerDef
// proto. Servers can be added to and removed from the list of remote workers
// in the context. New set of servers identified by the ServerDef must be up
// when the context is updated.
//
// This API is for experimental usage and may be subject to change.
TF_CAPI_EXPORT extern void TFE_ContextUpdateServerDef(TFE_Context* ctx,
                                                      int keep_alive_secs,
                                                      const void* proto,
                                                      size_t proto_len,
                                                      TF_Status* status);

// Checks whether a remote worker is alive or not. This will return true even if
// the context doesn't exist on the remote worker.
TF_CAPI_EXPORT extern bool TFE_ContextCheckAlive(TFE_Context* ctx,
                                                 const char* worker_name,
                                                 TF_Status* status);

// Clear pending streaming requests and error statuses on remote executors.
TF_CAPI_EXPORT extern void TFE_ContextClearRemoteExecutors(TFE_Context* ctx,
                                                           TF_Status* status);

// If the TensorHandle is copied to another device as part of an op execution,
// the copy is destroyed after the op has executed. Enabling implicit mirroring
// causes the copy to be held as a mirror for the lifetime of the TensorHandle.
TF_CAPI_EXPORT extern void TFE_TensorHandleEnableImplicitMirroring(
    TFE_TensorHandle*, TF_Status*);

// This function will block till the operation that produces `h` has
// completed. This is only valid on local TFE_TensorHandles. The pointer
// returned will be on the device in which the TFE_TensorHandle resides (so e.g.
// for a GPU tensor this will return a pointer to GPU memory). The pointer is
// only guaranteed to be valid until TFE_DeleteTensorHandle is called on this
// TensorHandle. Only supports POD data types.
TF_CAPI_EXPORT extern void* TFE_TensorHandleDevicePointer(TFE_TensorHandle*,
                                                          TF_Status*);

// This function will block till the operation that produces `h` has
// completed. This is only valid on local TFE_TensorHandles. Returns the size in
// bytes of the memory pointed to by the device pointer returned above.
TF_CAPI_EXPORT extern size_t TFE_TensorHandleDeviceMemorySize(TFE_TensorHandle*,
                                                              TF_Status*);

// Creates a new TensorHandle from memory residing in device_name. Takes
// ownership of the memory, and will call deleter to release it after TF
// no longer needs it or in case of error.
TF_CAPI_EXPORT extern TFE_TensorHandle* TFE_NewTensorHandleFromDeviceMemory(
    TFE_Context* ctx, const char* device_name, TF_DataType, const int64_t* dims,
    int num_dims, void* data, size_t len,
    void (*deallocator)(void* data, size_t len, void* arg),
    void* deallocator_arg, TF_Status* status);

// Retrieves the address space (i.e. job, replia, task) of the local host and
// saves it in the buffer.
TF_CAPI_EXPORT extern void TFE_HostAddressSpace(TFE_Context* ctx,
                                                TF_Buffer* buf);

// APIs for generically dealing with op attributes (e.g. when forwarding them
// through custom device implementations).
//
// TODO(allenl): Currently these are black boxes, but we should have some way to
// inspect values. This would let people e.g. copy over most attributes and then
// modify some based on their values.

// A reference to an op's name -> attribute mapping
typedef struct TFE_OpAttrs TFE_OpAttrs;

// Fetch a struct with a reference to information about attributes of `op`.
//
// The `attrs` struct does not own any memory, and `op` must outlive it.
TF_CAPI_EXPORT extern void TFE_OpGetAttrs(TFE_Op* op, TFE_OpAttrs* attrs);

// Add attributes in `attrs` to `op`.
//
// Does not overwrite or update existing attributes, but adds new ones.
TF_CAPI_EXPORT extern void TFE_OpAddAttrs(TFE_Op* op, const TFE_OpAttrs* attrs);

#define TFE_CUSTOM_DEVICE_VERSION 1

// Struct to be filled in
typedef struct TFE_CustomDevice {
  int version = TFE_CUSTOM_DEVICE_VERSION;
  // Method to copy a tensor to the custom device.
  TFE_TensorHandle* (*copy_tensor_to_device)(TFE_TensorHandle* tensor,
                                             TF_Status* status,
                                             void* device_info) = nullptr;

  // Method to copy a tensor from the custom device to a target device.
  TFE_TensorHandle* (*copy_tensor_from_device)(TFE_TensorHandle* tensor,
                                               const char* target_device_name,
                                               TF_Status* status,
                                               void* device_info);

  // Method to execute an operation.
  void (*execute)(int num_inputs, TFE_TensorHandle** inputs,
                  const char* operation_name, const TFE_OpAttrs* attributes,
                  int* num_outputs, TFE_TensorHandle** outputs, TF_Status* s,
                  void* device_info);

  // Method to delete a device.
  void (*delete_device)(void* device_info);
} TFE_CustomDevice;

// Registers a custom device for use with eager execution.
//
// Eager operations may be placed on this device, e.g.  `with
// tf.device("CUSTOM"):` from Python if `device_name` for this call is
// "/job:localhost/replica:0/task:0/device:CUSTOM:0".
//
// The custom device defines copy operations for moving TensorHandles on and
// off, and an an execution operation for named operations. Often execution will
// simply wrap op execution on one or more physical devices.
//
// device_info is an opaque caller-defined type stored with the custom device
// which is passed to the functions referenced in the TFE_CustomDevice struct
// `device` (execute, delete_device, etc.). It can for example contain the
// names of wrapped devices.
//
// There are currently no graph semantics implemented for registered custom
// devices, so executing tf.functions which contain operations placed on custom
// devices will fail.
//
// This API is highly experimental, and in particular is expected to change when
// it starts supporting operations with attributes and when tf.function support
// is added.
void TFE_RegisterCustomDevice(TFE_Context* ctx, TFE_CustomDevice device,
                              const char* device_name, void* device_info);

TF_CAPI_EXPORT extern void TFE_ContextGetFunctionDef(TFE_Context* ctx,
                                                     const char* function_name,
                                                     TF_Buffer* buf,
                                                     TF_Status* status);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  // TENSORFLOW_C_EAGER_C_API_EXPERIMENTAL_H_
