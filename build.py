import pathlib
import subprocess
import platform
import os

if platform.system() == "Windows":
    clang_exe = "C:\\Program Files\\LLVM\\bin\\clang++.exe"
else:
    clang_exe = "clang++"
    
BIN_PATH = "Bin"
DEBUG_MODE = False

if not os.path.exists(BIN_PATH):
    os.mkdir(BIN_PATH)

command = [
    clang_exe,
    "-o",
    f"{BIN_PATH}/Neon-{"Shipping" if DEBUG_MODE else "Developer"}-x64.exe",
    "-IModules/ui/include",
    "-IDeps/include",
    "-IPublic",
]

if platform.system() == "Windows":
    command = [
        *command,
        "-lDeps/SDL3-static.lib",
        "-lDeps/SDL3_ttf.lib",
        "-lDeps/SDL3_image-static.lib",
        "-lUser32.lib",
        "-lShell32.lib",
        "-lOle32.lib",
        "-lGdi32.lib",
        "-lImm32.lib",
        "-lVersion.lib",
        "-lCfgmgr32.lib",
        "-lOleAut32.lib",
        "-lAdvapi32.lib",
        "-lWinmm.lib",
        "-lSetupapi.lib",
        "-lUsp10.lib",
        "-lRpcrt4.lib"
    ]

with open("debug_mode.txt", "r") as debug:
    if debug.read() == "enable":
        command = [
            *command,
            "-llibcpmtd.lib",
            "-llibcmtd.lib",
            "-fms-runtime-lib=static_dbg",
            "-lDeps/freetype.lib",
            "-Wl,/NODEFAULTLIB:libcmt.lib"
        ]

def push_if_file(path: pathlib.Path):
    if path.is_file():
        command.append(str(path))

for source in pathlib.Path("Src").glob("*.cc"):
    push_if_file(source)
    
for source in pathlib.Path("Modules").glob("**/*.cc"):
    push_if_file(source)
    
print(" ".join(command))
subprocess.call(command)