#SurfaceTexture

##1 

###1.1 

`
/**
 * Captures frames from an image stream as an OpenGL ES texture.
 *
 * <p>The image stream may come from either camera preview or video decode. A
 * {@link android.view.Surface} created from a SurfaceTexture can be used as an output
 * destination for the {@link android.hardware.camera2}, {@link android.media.MediaCodec},
 * {@link android.media.MediaPlayer}, and {@link android.renderscript.Allocation} APIs.
 * When {@link #updateTexImage} is called, the contents of the texture object specified
 * when the SurfaceTexture was created are updated to contain the most recent image from the image
 * stream.  This may cause some frames of the stream to be skipped.
 *
`
把一个图像流作为一个GLES纹理来采集帧
图像流可能来自摄像头预览或者是视频解码。
通过SurfaceTextu创建的Surface ，可以用来作为camera2、mediacodec、mediaplayer的输出目的地。
调用updateTexImage时，当SurfaceTexture已经被创建后，指定的纹理对象的内容会呗更新以含有来自image流的最近的图像。
这可能会引起流的一些图像被跳过。

###1.2 
`
 * <p>A SurfaceTexture may also be used in place of a SurfaceHolder when specifying the output
 * destination of the older {@link android.hardware.Camera} API. Doing so will cause all the
 * frames from the image stream to be sent to the SurfaceTexture object rather than to the device's
 * display.
 *
`
一个SurfaceTexut可能会被用于替代SurfaceHolder作为Camera的目的地。
这样做 的结果是所有的来自图像流的frame会被发送到一个SurfaceTexture对象而不是送到设备的显示器。


###1.3 

`

 * <p>When sampling from the texture one should first transform the texture coordinates using the
 * matrix queried via {@link #getTransformMatrix(float[])}.  The transform matrix may change each
 * time {@link #updateTexImage} is called, so it should be re-queried each time the texture image
 * is updated.
 * This matrix transforms traditional 2D OpenGL ES texture coordinate column vectors of the form (s,
 * t, 0, 1) where s and t are on the inclusive interval [0, 1] to the proper sampling location in
 * the streamed texture.  This transform compensates for any properties of the image stream source
 * that cause it to appear different from a traditional OpenGL ES texture.  For example, sampling
 * from the bottom left corner of the image can be accomplished by transforming the column vector
 * (0, 0, 0, 1) using the queried matrix, while sampling from the top right corner of the image can
 * be done by transforming (1, 1, 0, 1).
 *
`
当通过这个纹理进行采样时，必需首先对纹理坐标进行转换，转换矩阵通过getTransformMatrix(float[])搞定。
转换矩阵可能会在每次updateTexImage被调用时被改变，所以必需在每次纹理图像被更新的时候重新请求。
这个矩阵可以转换传统的2D gles 列向量形式的纹理坐标（(s, * t, 0, 1)  s 和t 是在 [0,1] 范围内） 到被stream了的纹理的合适的采样位置。（啥东东？）
这个转换可以补偿image 流源 任意的 properties，所以会让这个转换跟传统的gles纹理不同。
/*TODO 翻译*/
比如说，从图形的底部左边角落 采样，可以通过queried的矩阵的转换列向量 （0,0,0,1）来实现，从图像右上角采样可以通过转换矩阵（1，1,0,1）来实现。


## 1.4 
`

 * <p>The texture object uses the GL_TEXTURE_EXTERNAL_OES texture target, which is defined by the
 * <a href="http://www.khronos.org/registry/gles/extensions/OES/OES_EGL_image_external.txt">
 * GL_OES_EGL_image_external</a> OpenGL ES extension.  This limits how the texture may be used.
 * Each time the texture is bound it must be bound to the GL_TEXTURE_EXTERNAL_OES target rather than
 * the GL_TEXTURE_2D target.  Additionally, any OpenGL ES 2.0 shader that samples from the texture
 * must declare its use of this extension using, for example, an "#extension
 * GL_OES_EGL_image_external : require" directive.  Such shaders must also access the texture using
 * the samplerExternalOES GLSL sampler type.
 *
`
纹理对象使用GL_TEXTURE_EXTERNAL_OES 纹理目标，这个是由OES_EGL_image_external.txt 定义的。
这是gles扩展，用于限制纹理如何使用。
每次纹理被bound，必需bound到一个GL_TEXTURE_EXTERNAL_OES 目标，而不是一个GL_TEXTURE_2D 目标。
另外，任意的从纹理采样的gles2.0的shader 必需声明自己使用这个扩展，比如说 #extension GL_OES_EGL_image_external : require  指令。
 这样的一个shader必需也要使用samplerExternalOES GLSL 采样类型来访问纹理。


### 1.5 

 `
 * <p>SurfaceTexture objects may be created on any thread.  {@link #updateTexImage} may only be
 * called on the thread with the OpenGL ES context that contains the texture object.  The
 * frame-available callback is called on an arbitrary thread, so unless special care is taken {@link
 * #updateTexImage} should not be called directly from the callback.
 */

 `

SurfaceTexture对象可被在任意线程创建，updateTexImage仅能在含有纹理对象的GLES上下文的线程调用。

frame-available 回调必需在任意线程上调用，所以除非采取了特殊的保护，updateTexImage 不能直接在 frame-available回调中使用。


##2   

###2.1 
`

public class SurfaceTexture {
    private final Looper mCreatorLooper;
    private Handler mOnFrameAvailableHandler;

    /**
     * These fields are used by native code, do not access or modify.  本地代码使用，不要修改
     */
    private long mSurfaceTexture;
    private long mProducer;
    private long mFrameAvailableListener;

    /**
     * Callback interface for being notified that a new stream frame is available.  这是huidaio9，用户通知一个新的stream frame 可用，传递过来的是一个surfaceTexture 
     */
    public interface OnFrameAvailableListener {
        void onFrameAvailable(SurfaceTexture surfaceTexture);
    }

    /**
     * Exception thrown when a SurfaceTexture couldn't be created or resized.   这个接口不用了
     *
     * @deprecated No longer thrown. {@link android.view.Surface.OutOfResourcesException}
     * is used instead.
     */
    @SuppressWarnings("serial")
    @Deprecated
    public static class OutOfResourcesException extends Exception {
        public OutOfResourcesException() {
        }
        public OutOfResourcesException(String name) {
            super(name);
        }
    }

    /**  为一个给定的GL 纹理， 构造一个新的SurfaceTexture 用于 stream image ，
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     * @param texName the OpenGL texture object name (e.g. generated via glGenTextures)
     *
     * @throws Surface.OutOfResourcesException If the SurfaceTexture cannot be created. 抛出一个无法创建的异常
     */
    public SurfaceTexture(int texName 这是opengl纹理对象的名字，可以通过glGenTextures 产生 ) {
        this(texName, false);
    }


    `
### 2.2 

    `
    /**
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     在缓冲单个的模式下，应用程序负责串行序列化的访问图像内容缓冲。
     每次图像内容缓冲被更新，releaseTexImage 方法必需在图像内容生产者接管这个buffer的所有权之前调用。
     比如说，当通过NDK的方法 ANativeWindow_lock and ANativeWindow_unlockAndPost  产生 生产图像（意思是显示？）的时候，
     releaseTexImage 必需在每个ANativeWindow_lock 之前调用，否则调用会失败。
     当使用 GLES生产图像内容的时候，releaseTexImage必需在第一个GLES函数调用每个frame之前被调用。 （怎么具体点）

     * In single buffered mode the application is responsible for serializing access to the image
     * content buffer. Each time the image content is to be updated, the
     * {@link #releaseTexImage()} method must be called before the image content producer takes
     * ownership of the buffer. For example, when producing image content with the NDK
     * ANativeWindow_lock and ANativeWindow_unlockAndPost functions, {@link #releaseTexImage()}
     * must be called before each ANativeWindow_lock, or that call will fail. When producing
     * image content with OpenGL ES, {@link #releaseTexImage()} must be called before the first
     * OpenGL ES function call each frame.
     *
     * @param texName the OpenGL texture object name (e.g. generated via glGenTextures)
     * @param singleBufferMode whether the SurfaceTexture will be in single buffered mode.
     *
     * @throws Surface.OutOfResourcesException If the SurfaceTexture cannot be created.
     */
    public SurfaceTexture(int texName 纹理对象的名字  , boolean singleBufferMode) {
        mCreatorLooper = Looper.myLooper();
        nativeInit(false, texName, singleBufferMode, new WeakReference<SurfaceTexture>(this));
    }
    `

### 2.3 

-- 这个函数没有传递纹理对象的名字，怎么破？
    `

    /**
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     * In single buffered mode the application is responsible for serializing access to the image
     * content buffer. Each time the image content is to be updated, the
     * {@link #releaseTexImage()} method must be called before the image content producer takes
     * ownership of the buffer. For example, when producing image content with the NDK
     * ANativeWindow_lock and ANativeWindow_unlockAndPost functions, {@link #releaseTexImage()}
     * must be called before each ANativeWindow_lock, or that call will fail. When producing
     * image content with OpenGL ES, {@link #releaseTexImage()} must be called before the first
     * OpenGL ES function call each frame.
     *
     * Unlike {@link #SurfaceTexture(int, boolean)}, which takes an OpenGL texture object name,
     * this constructor creates the SurfaceTexture in detached mode. A texture name must be passed
     * in using {@link #attachToGLContext} before calling {@link #releaseTexImage()} and producing
     * image content using OpenGL ES.
     *
由于没有用传递纹理对象的名字，所以构造函数必需在detached模式下，创建一个SurfaceTexture。
一个纹理的名字必需在调用releaseTexImage 和使用GLES来 产生图像内容之前， 使用attachToGLContext 来创建。

     * @param singleBufferMode whether the SurfaceTexture will be in single buffered mode.
     *
     * @throws Surface.OutOfResourcesException If the SurfaceTexture cannot be created.
     * @hide
     */
    public SurfaceTexture(boolean singleBufferMode) {
        mCreatorLooper = Looper.myLooper();
        nativeInit(true, 0, singleBufferMode, new WeakReference<SurfaceTexture>(this));
    }

`
###2.4 得首先绑定GLES上下文

`

    /**
     * Register a callback to be invoked when a new image frame becomes available to the
     * SurfaceTexture.   
     注册一个回调，当一个新的图像frame变得对SurfaceTexture可用的时候，可以被调用。
     * <p>
     * The callback may be called on an arbitrary thread, so it is not
     * safe to call {@link #updateTexImage} without first binding the OpenGL ES context to the
     * thread invoking the callback.
     * </p>
     *
     这个回调，可以在任意的线程中被调用。
     所以，这个回调如果不首先绑定OPENGLES的上下文到调用这个回调方法的线程上，就被调用了，是非常危险的。
     * @param listener The listener to use, or null to remove the listener.
     */
    public void setOnFrameAvailableListener(@Nullable OnFrameAvailableListener listener) {
        setOnFrameAvailableListener(listener, null);
    }


### 2.5  新增一个Handler

    /**
     * Register a callback to be invoked when a new image frame becomes available to the
     * SurfaceTexture.
     * <p>
     * If a handler is specified, the callback will be invoked on that handler's thread.
     * If no handler is specified, then the callback may be called on an arbitrary thread,
     * so it is not safe to call {@link #updateTexImage} without first binding the OpenGL ES
     * context to the thread invoking the callback.
     * </p>
     *
     如果指定了handler，回调会在handler的thread中被调用。
     如果没有指定handler，那么回调可能在任意线程中被调用，所以如果不首先绑定GLES上下文到调用这个回调的线程就去调用updateTexImage是不安全的。
     * @param listener The listener to use, or null to remove the listener.
     * @param handler The handler on which the listener should be invoked, or null
     * to use an arbitrary thread.
     */
    public void setOnFrameAvailableListener(@Nullable final OnFrameAvailableListener listener,
            @Nullable Handler handler) {
        if (listener != null) {
            // Although we claim the thread is arbitrary, earlier implementation would
            // prefer to send the callback on the creating looper or the main looper
            // so we preserve this behavior here.
            尽管，我们声称这个线程是任意的， 但早起的实现更倾向于发送回调给 creating looper 或者 main looper ，所以这些行为保留。
            Looper looper = handler != null ? handler.getLooper() :
                    mCreatorLooper != null ? mCreatorLooper : Looper.getMainLooper();
            mOnFrameAvailableHandler = new Handler(looper, null, true /*async*/) {
                @Override
                public void handleMessage(Message msg) {
                    listener.onFrameAvailable(SurfaceTexture.this);
                }
            };
        } else {
            mOnFrameAvailableHandler = null;
        }
    }
`
### 2.6 设置图像缓冲的默认大小
`

    /**
     * Set the default size of the image buffers.  The image producer may override the buffer size,
     * in which case the producer-set buffer size will be used, not the default size set by this
     * method.  Both video and camera based image producers do override the size.  This method may
     * be used to set the image size when producing images with {@link android.graphics.Canvas} (via
     * {@link android.view.Surface#lockCanvas}), or OpenGL ES (via an EGLSurface).
     *
     设置图像缓冲的默认大小。
     图像生产者 可能会覆盖 buffer 大小，在这种情况下生产者设置的buffer大小是可以被使用的，并不是这个方法所设定的默认大小。
     video和基于图像生产者的camera 都会覆盖这个大小，这方法可以适用于 使用 android.graphics.Canvas （通过android.view.Surface#lockCanvas）或者OPENGLES （通过EGLSurface）来生产图像时，设置图像大小。

     * The new default buffer size will take effect the next time the image producer requests a
     * buffer to fill.  For {@link android.graphics.Canvas} this will be the next time {@link
     * android.view.Surface#lockCanvas} is called.  For OpenGL ES, the EGLSurface should be
     * destroyed (via eglDestroySurface), made not-current (via eglMakeCurrent), and then recreated
     * (via eglCreateWindowSurface) to ensure that the new default size has taken effect.
     默认的缓冲大小，会在下一次图像生产者请求一个buffer来填充的时候生效。
     对于canvas，是下一次lockCavas被调用的时候生效。
     对于GLES，当通过eglDestroySurface来摧毁EGLSurface，且 是 not-current （通过eglMakeCurrent），然后，重新创建（通过eglCreateWindowSurface），来确保新的默认大小会生效。
     *

     * The width and height parameters must be no greater than the minimum of
     * GL_MAX_VIEWPORT_DIMS and GL_MAX_TEXTURE_SIZE (see
     * {@link javax.microedition.khronos.opengles.GL10#glGetIntegerv glGetIntegerv}).
     * An error due to invalid dimensions might not be reported until
     * updateTexImage() is called.
     */
     宽度和高度参数必需不能比 GL_MAX_VIEWPORT_DIMS 和 GL_MAX_TEXTURE_SIZE的最小值大
     否则，会因为不恰当的分辨率报错，直到再一次调用 updateTexImage
    public void setDefaultBufferSize(int width, int height) {
        nativeSetDefaultBufferSize(width, height);
    }
`

### 2.7  更新texture image 为来自image 流的 最 近  的frame

`
    /**
     * Update the texture image to the most recent frame from the image stream.  This may only be
     * called while the OpenGL ES context that owns the texture is current on the calling thread.
     * It will implicitly bind its texture to the GL_TEXTURE_EXTERNAL_OES texture target.
     */
     仅当OPENGLSES 上下文被当前调用这个方法的线程上拥有的时候，才能被调用。
     这个会默默的把自己的texture 绑定到GL_TEXTURE_EXTERNAL_OES 纹理对象上。
    public void updateTexImage() {
        nativeUpdateTexImage();
    }
`

### 2.8  releaseTexImage
`
    /**
     * Releases the the texture content. This is needed in single buffered mode to allow the image
     * content producer to take ownership of the image buffer.
     * For more information see {@link #SurfaceTexture(int, boolean)}.
     */
     释放纹理上下文，这在缓冲单个的模式下被需要以允许图像内容生产者可以接管image buffer。
    public void releaseTexImage() {
        nativeReleaseTexImage();
    }

`

 ### 2.9 detachFromGLContext 允许从拥有OPENGLES纹理对象的OPENGLES上下文detach这个SurfaceTexture

 `
    /**
     * Detach the SurfaceTexture from the OpenGL ES context that owns the OpenGL ES texture object.
     * This call must be made with the OpenGL ES context current on the calling thread.  The OpenGL
     * ES texture object will be deleted as a result of this call.  After calling this method all
     * calls to {@link #updateTexImage} will throw an {@link java.lang.IllegalStateException} until
     * a successful call to {@link #attachToGLContext} is made.
     *
     这次调用之后，这个OPENGLES 纹理对象会被删除。
     调用之后，对updateTexImage的所有调用会抛出一个状态非法的异常，直到成功调用了attachToGLContext。

     * This can be used to access the SurfaceTexture image contents from multiple OpenGL ES
     * contexts.  Note, however, that the image contents are only accessible from one OpenGL ES
     * context at a time.
可以用多个opengles的上下文访问SurfaceTexture 图片内容。
记住，图像内容仅仅在一个OPENGLES的上下文访问一次。 （啥意思？）

     */
    public void detachFromGLContext() {
        int err = nativeDetachFromGLContext();
        if (err != 0) {
            throw new RuntimeException("Error during detachFromGLContext (see logcat for details)");
        }
    }

`


### 2.10 

`
    /**
     * Attach the SurfaceTexture to the OpenGL ES context that is current on the calling thread.  A
     * new OpenGL ES texture object is created and populated with the SurfaceTexture image frame
     * that was current at the time of the last call to {@link #detachFromGLContext}.  This new
     * texture is bound to the GL_TEXTURE_EXTERNAL_OES texture target.
     *
attach这个纹理到当前正在调用线程的OPENGLES的上下文。
一个新的OPENGLES文件对象会被创建，并且使用一个纹理图像frame填充，这个frame是来自于上一次调用detachFromGLContext时的当前的纹理图像frame。（啥情况？）
这个纹理会绑定到GL_TEXTURE_EXTERNAL_OES的纹理目标。


     * This can be used to access the SurfaceTexture image contents from multiple OpenGL ES
     * contexts.  Note, however, that the image contents are only accessible from one OpenGL ES
     * context at a time.
这允许可以从多个GLES的上下文来访问纹理图像内容。

但是，请注意，图像内容只能从一个OpenGL ES访问      *上下文一次。  （TODO 谷歌翻译的）
     *
     * @param texName The name of the OpenGL ES texture that will be created.  This texture name
     * must be unusued in the OpenGL ES context that is current on the calling thread.
     */
    public void attachToGLContext(int texName) {
        int err = nativeAttachToGLContext(texName);
        if (err != 0) {
            throw new RuntimeException("Error during attachToGLContext (see logcat for details)");
        }
    }
`


###2.11
`
    /**
     * Retrieve the 4x4 texture coordinate transform matrix associated with the texture image set by
     * the most recent call to updateTexImage.
     * 保存与纹理图像相关的4*4的纹理坐标转换矩阵，这个矩阵是从最近一次对updateTexImage的调用设置的。
     矩阵的形式是 （s，t，0,1） ，s和t是【0,1】范围内的，要用这来对纹理的位置采样。
     如果在这个范围外采样的话，转换是未定义的。

     * This transform matrix maps 2D homogeneous texture coordinates of the form (s, t, 0, 1) with s
     * and t in the inclusive包括的 range [0, 1] to the texture coordinate that should be used to sample
     * that location from the texture.  Sampling the texture outside of the range of this transform
     * is undefined.
     *
     * The matrix is stored in column-major order so that it may be passed directly to OpenGL ES via
     * the glLoadMatrixf or glUniformMatrix4fv functions.
     矩阵的存储是 以列为主的，所以，可以直接通过glLoadMatrixf 或者 glUniformMatrix4fv 函数传递到opengles中。 *
     矩阵  存在 float【】数组中，存的是4*4的矩阵， 有16个元素。

     * @param mtx the array into which the 4x4 matrix will be stored.  The array must have exactly
     *     16 elements.
     */
    public void getTransformMatrix(float[] mtx) {
        // Note we intentionally don't check mtx for null, so this will result in a
        // NullPointerException. But it's safe because it happens before the call to native.
        if (mtx.length != 16) {
            throw new IllegalArgumentException();
        }
        nativeGetTransformMatrix(mtx);
    }

`


##2.12 获取最近一次调用updateTexImage时被设置的texture image 的时间戳（纳秒）
`
    /**
     * Retrieve the timestamp associated with the texture image set by the most recent call to
     * updateTexImage.
     *

     * This timestamp is in nanoseconds, and is normally monotonically increasing. The timestamp
     * should be unaffected by time-of-day adjustments, and for a camera should be strictly
     * monotonic but for a MediaPlayer may be reset when the position is set.  The
     * specific meaning and zero point of the timestamp depends on the source providing images to
     * the SurfaceTexture. Unless otherwise specified by the image source, timestamps cannot
     * generally be compared across SurfaceTexture instances, or across multiple program
     * invocations. It is mostly useful for determining time offsets between subsequent frames.
     */
     这时间戳是纳秒，一般是单调递增的，时间戳应该不会被time-of-day的矫正锁影响，对于一个camera来说，应该是严格的单调的，但是对于一个MediaPlayer来说，
     可能会因为position被设置之后而改变。
     这是有意义的，而且 时间戳的0点，依赖于提供images 给SurfaceTexture的源。
     除了其image source指定的例外的情况，时间戳不能跨 SurfaceTexture例程来比较，或者挎着多个程序调用。
     这在大多数情况下是有用的，可以决定随后的frames 的时间偏移量。

    public long getTimestamp() {
        return nativeGetTimestamp();
    }


## 2.13 

    /**
     * release() frees all the buffers and puts the SurfaceTexture into the
     * 'abandoned' state. Once put in this state the SurfaceTexture can never
     * leave it. When in the 'abandoned' state, all methods of the
     * IGraphicBufferProducer interface will fail with the NO_INIT error.
     释放所有的缓冲，并且把这个SurfaceTexture放到'abandoned'状态。
     一旦把SurfaceTexture 置为废弃态，那么SurfaceTexture 就再也不会离开了。
     废弃态下，IGraphicBufferProducer 接口的所有方法会以NO_INIT错误失败。

     * Note that while calling this method causes all the buffers to be freed
     * from the perspective of the the SurfaceTexture, if there are additional
     * references on the buffers (e.g. if a buffer is referenced by a client or
     * by OpenGL ES as a texture) then those buffer will remain allocated.
     *
注意，一旦调用了这个方法，从SurfaceTexture的视角来看，所有的缓冲都会被释放掉，如果有额外的对这些缓冲的引用，
比如说一个缓冲被一个客户端引用 或者被一个OPENGLES作为一个纹理 ，那么这些缓冲会保持着 被分配的状态。

     * Always call this method when you are done with SurfaceTexture. Failing
     * to do so may delay resource deallocation for a significant amount of
     * time.
     如果使用SurfaceTexture完，经常调用这个方法。不调用的话，会导致很多资源的回收被延时的，会很耗时。
     */
    public void release() {
        nativeRelease();
    }

    /**
     * Returns true if the SurfaceTexture was released
     * @hide
     */
    public boolean isReleased() {
        return nativeIsReleased();
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            nativeFinalize();
        } finally {
            super.finalize();
        }
    }

`



    /**
     * This method is invoked from native code only.
     */
    @SuppressWarnings({"UnusedDeclaration"})
    private static void postEventFromNative(WeakReference<SurfaceTexture> weakSelf) {
        SurfaceTexture st = weakSelf.get();
        if (st != null) {
            Handler handler = st.mOnFrameAvailableHandler;
            if (handler != null) {
                handler.sendEmptyMessage(0);
            }
        }
    }

    private native void nativeInit(boolean isDetached, int texName,
            boolean singleBufferMode, WeakReference<SurfaceTexture> weakSelf)
            throws Surface.OutOfResourcesException;
    private native void nativeFinalize();
    private native void nativeGetTransformMatrix(float[] mtx);
    private native long nativeGetTimestamp();
    private native void nativeSetDefaultBufferSize(int width, int height);
    private native void nativeUpdateTexImage();
    private native void nativeReleaseTexImage();
    private native int nativeDetachFromGLContext();
    private native int nativeAttachToGLContext(int texName);
    private native int nativeGetQueuedCount();
    private native void nativeRelease();
    private native boolean nativeIsReleased();

    /*
     * We use a class initializer to allow the native code to cache some
     * field offsets.
     */
    private static native void nativeClassInit();
    static { nativeClassInit(); }
}
`