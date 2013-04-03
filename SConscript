#-*- python -*-

# Sconscript for the Uaapi library. Returns the paths to the built
# dynamic libraries (1 for now).
# Call this SConscript in your SConstruct file

env = Environment()

includeDir = Dir("include/")

env["CPPPATH"] = includeDir
env["CPPDEFINES"] = [env["PLATFORM"].upper(), "UAAPI_EXPORT"]

if env["PLATFORM"] == "win32":
    env["CCFLAGS"].append("/EHsc")
elif env["PLATFORM"] == "posix":
    env["CCFLAGS"].append("-g")

Export("env")

dlFiles = SConscript("src/SConscript")
Return("dlFiles")
