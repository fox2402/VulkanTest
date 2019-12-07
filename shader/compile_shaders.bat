echo "compiling shader.vert..."

C:/VulkanSDK/1.1.121.2/Bin32/glslc.exe shader.vert -o vert.spv

echo "Done."
echo "compiling shader.frag..."

C:/VulkanSDK/1.1.121.2/Bin32/glslc.exe shader.frag -o frag.spv
echo "Done."


pause