![ten-trillion-logo](readme/ten-trillion-logo.png)

# The TenTrillion Game Engine

The TenTrillion Game Engine is an optimized game engine meant for extremely quick rendering and fast performance.

The main goal of the TenTrillion, is to provide optimizations for games, so developers don't have to write them
manually.

Along with taking full advantage of the user's GPU and CPU with OpenCL.

> [!IMPORTANT]
> This portion of the TenTrillion is the SDK. You can use this portion of it to make anything as barebones as possible,
> but for a better experience, use the upcoming editor.

## Requirements

- Vulkan *(Optional, If your system doesn't support Vulkan, the TenTrillion will use the OpenGL renderer.)*
- OpenGL
- OpenCL
- OpenAL

> [!NOTE]
> You don't have to install GLFW, VulkanHeaders or volk manually. They will be provided by the git submodules.
>
> Clone the submodules using `git submodule update --init --recursive`

## Building

Firstly, create a build directory where your build files will reside.

After you created the folder, in the ROOT directory of the TenTrillion Project:

```shell
cmake -S . -B build # The name of your folder after the --build flag must be specified.
cmake --build build # You can name it just 'build' to be simple.
```

Since the SDK is just one library file, you have built the TenTrillion. For easier usage, It is recommended for you to
use the pre-compiled libraries in the 'Releases' section.

## License

This project uses the MIT License. Check out the [LICENSE](LICENSE) file for more information.
