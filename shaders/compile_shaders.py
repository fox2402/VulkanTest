import os
import subprocess

for filename in os.listdir("."):
  if filename.endswith(".frag") or filename.endswith(".vert"):
    subprocess.run([os.environ['VULKAN_SDK'] + os.path.sep + "Bin32" + os.path.sep + "glslc.exe", filename, "-o", filename[:-5] + ".spv"])