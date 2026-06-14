# Removing previous distributive package
Remove-Item ".\dist\*.*" -Force
Remove-Item ".\dist" -Recurse -Force

# Creating new distributive folder
New-Item -Path ".\dist" -ItemType Directory

# Copying StG distributives
Copy-Item -Path ".\StG\bin\Release\StG.exe" -Destination ".\dist"
Copy-Item -Path ".\StG\bin\Release\AESBridge.dll" -Destination ".\dist"
Copy-Item -Path ".\StG\bin\Release\StGBridge.dll" -Destination ".\dist"

# Copying OpenCV lib
Copy-Item -Path "C:\opencv\build\x64\vc16\bin\opencv_world4120.dll" -Destination ".\dist"

# Copying documentation
Copy-Item -Path ".\docs\Readme.pdf" -Destination ".\dist"
Copy-Item -Path ".\docs\License.pdf" -Destination ".\dist"
Copy-Item -Path ".\OpenCV.txt" -Destination ".\dist"

# Compress archive
Compress-Archive -Path ".\dist\*" -Destination ".\dist\StG_$(Get-Date -Format 'yyyy-MM-dd_HH-mm-ss').zip"


PAUSE