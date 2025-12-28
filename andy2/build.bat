echo "Starting build..."
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" andycad.sln -t:Rebuild -p:Configuration=Debug -p:Platform=x64 > build_attempt_10_bat.log 2>&1
echo "Build finished."