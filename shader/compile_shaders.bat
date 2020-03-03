echo "compiling shader.vert..."

%VULKAN_SDK%\Bin32\glslc.exe shader.vert -o vert.spv

echo "Done."
echo "compiling shader.frag..."

%VULKAN_SDK%\Bin32\glslc.exe shader.frag -o frag.spv
echo "Done."


pause