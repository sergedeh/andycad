; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=AndyCAD
AppVersion=0.91
DefaultDirName={pf}\AndyCAD
DefaultGroupName=AndyCAD
UninstallDisplayIcon={app}\andycad.exe
Compression=lzma2
SolidCompression=yes
OutputBaseFilename=AndyCAD
OutputDir=userdocs:Inno Setup Examples Output

[Files]
Source: "C:\Program Files(uac)\MyProjects\andycad\Debug\andycad.exe"; DestDir: "{app}"
;Source: "C:\Program Files(uac)\MyProjects\andycad\Release\andycad.exe"; DestDir: "{app}"
Source: "C:\Program Files(uac)\MyProjects\andycad\cad.chm"; DestDir: "{app}"
Source: "C:\Program Files(uac)\MyProjects\andycad\andycad_bar.reg"; DestDir: "{app}"
Source: "C:\Program Files(uac)\MyProjects\andycad\texture\*.*"; DestDir: "{app}\texture"
Source: "C:\Program Files(uac)\MyProjects\andycad\Library\*.*"; DestDir: "{app}\Library"
Source: "c:\windows\system32\MFC42D.DLL"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall allowunsafefiles
Source: "c:\windows\system32\MSVCRTD.DLL"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall allowunsafefiles
Source: "c:\windows\system32\MFCO42D.DLL"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall allowunsafefiles
Source: "c:\windows\system32\MSVCP60D.DLL"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall allowunsafefiles
;Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\AndyCAD"; Filename: "{app}\andycad.exe";
[Run]
Filename: "reg"; Parameters: "import andycad_bar.reg";Description: "Import the Toolbar State"; Flags: shellexec;WorkingDir: "{app}"

[Registry]
Root: "HKLM";Subkey:"SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers"; ValueType:String;ValueName:"{app}\andycad.exe";ValueData:"RUNASADMIN";Flags:uninsdeletekeyifempty uninsdeletevalue;MinVersion: 0,6.1
Root: "HKLM64";Subkey:"SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers"; ValueType:String;ValueName:"{app}\andycad.exe";ValueData:"RUNASADMIN";Flags:uninsdeletekeyifempty uninsdeletevalue;MinVersion: 0,6.1;Check: IsWin64 
