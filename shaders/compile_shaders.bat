echo "compiling shader.vert..."

%VULKAN_SDK%\Bin\glslc.exe vert.vert -o vert.spv
echo "Done."

pause

echo "compiling shader.frag..."

%VULKAN_SDK%\Bin\glslc.exe frag.frag -o frag.spv
echo "Done."


pause