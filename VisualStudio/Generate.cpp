#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <utility>
#include <Rpc.h>  // needed for UUID functions
#pragma comment(lib, "Rpcrt4.lib")

namespace fs = std::experimental::filesystem;
using std::cout;
using std::move;
using std::string;

//const fs::path basepath {"E:\\C++Libs\\Range-V3-VS2015"};  // where the sln file is located
#define QUOTE2(a) #a
#define QUOTEIT(a) QUOTE2(a)
const fs::path basepath { QUOTEIT(SOLUTION_DIR) };  // where the sln file is located
const fs::path testdir = basepath/"test";
const fs::path projdir = basepath/"VisualStudio";

fs::path relative_name (fs::path name)
{
	// I expect the names found under the directory starting point will begin with that
	// exact same string (and a separator), and everything after that is what I want.
	static const size_t testdir_len= testdir.native().size();
	auto s {name.native()};
	auto start_here { s.cbegin() + testdir_len+1 };
	return { start_here, s.cend() };
}


string generate_GUID()
{
	UUID uuid;
	::UuidCreate(&uuid);
	unsigned char* s {nullptr};
	::UuidToStringA (&uuid, &s);
	string result{reinterpret_cast<char*>(s)};
	if (s)  ::RpcStringFreeA(&s);
	return result;
}

void write_template (std::ostream& out, string folder, string local, const string& GUID)
{
	// want "local" as the file name without the .cpp part.
	// Since there are only a couple blanks to fill in, just do it with brute force.
	if (!folder.empty()) folder.push_back('\\');
	out << 
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<Project DefaultTargets=\"Build\" ToolsVersion=\"15.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n"
		"\n"
		"  <PropertyGroup Label=\"ConfigHandy\">\n"
		"    <CH_local>" << local << "</CH_local>\n"
		"    <CH_folder>" << folder << "</CH_folder>\n"
		"  </PropertyGroup>\n"
		"\n"
		"  <Import Project=\"$(SolutionDir)VisualStudio\\COMMON.vcxproj\" />\n"
		"\n"
		"  <PropertyGroup Label=\"Globals\">\n"
		"    <ProjectGuid>{" << GUID << "}</ProjectGuid>\n"
		"  </PropertyGroup>\n"
		"\n"
		"  <ItemGroup>\n"
		"    <ClCompile Remove=\"Generate.cpp\" />\n"
		"    <ClCompile Include=\"$(SolutionDir)test\\$(CH_folder)$(CH_local).cpp\" />\n"
		"  </ItemGroup>\n"
		"\n"
		"</Project>";
}


// store details for writing the sln file info later
struct proj { string uuid, name, filename; };
std::vector<proj> projlist;

void process (fs::path folder, fs::path local)
{
	auto dir= projdir/folder;
	fs::create_directories (dir);  // does nothing if it already exists
	std::ofstream outfile { dir/local+=".vcxproj" };
	auto GUID= generate_GUID();
	write_template (outfile, folder.string(), local.string(), GUID);
	// also leave information for pasting into .sln file
	projlist.push_back({GUID, local.string(), (folder/local).string()});
}


void write_sln()
{
	std::ofstream out {projdir/"!sln_notes.txt"};
	out << "Paste these sections into the proper places into the SLN file.\n\n";
	out << "#### TOP PART\n\n";
	for (const auto& item : projlist) {
		out << R"qq(Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = ")qq"  << item.name << R"qq(", "VisualStudio\)qq"  << item.filename << R"qq(.vcxproj", "{)qq"  << item.uuid << R"qq(}")qq";
		out << "\nEndProject\n";
	}
	out << "\n\n\n#### BOTTOM PART\n\n";
	for (const auto& item : projlist) {
		out << "\t\t{" << item.uuid << "}.Debug|x64.ActiveCfg = Debug|x64\n";
		out << "\t\t{" << item.uuid << "}.Debug|x64.Build.0 = Debug|x64\n";
		out << "\t\t{" << item.uuid << "}.Debug|x86.ActiveCfg = Debug|Win32\n";
		out << "\t\t{" << item.uuid << "}.Debug|x86.Build.0 = Debug|Win32\n";
		out << "\t\t{" << item.uuid << "}.Release|x64.ActiveCfg = Release|x64\n";
		out << "\t\t{" << item.uuid << "}.Release|x64.Build.0 = Release|x64\n";
		out << "\t\t{" << item.uuid << "}.Release|x86.ActiveCfg = Release|Win32\n";
		out << "\t\t{" << item.uuid << "}.Release|x86.Build.0 = Release|Win32\n";
	}
}


void show_usage()
{
	cout << "You probably don't want to run this.\n"
		"The many small test programs are individual vcxproj project files, but they are\n"
		"small stubs that refer back to COMMON.vcxproj for all the actual settings.  So,\n"
		"you can set everything in ONE PLACE, and not separately for a bunch of individual\n"
		"projects!  Furthermore, COMMON is a normal project so it can be manipulated by\n"
		"the Properties GUI in the IDE, rather than tended by hand.  In order to reveal\n"
		"C++ compiler settings, the project has to have at least one .cpp file in it.\n"
		"So, it generates a program when compiled on its own, too.  That is this EXE.\n"
		"Now, to be extra clever and parsimonious, this .cpp file happens to be the\n"
		"program that generates all the project files for all the test/**/*.cpp files\n"
		"that are present.  To really run that, rename the file to Generate.exe and\n"
		"also give it a command-line argument.\n\n";
}

int main (int argc, char *argv[])
{
	fs::path arg0 {argv[0]};
	if(argc < 2 || arg0.filename().stem() == "COMMON") {
		show_usage();
		return 1;
	}
	cout << "arg[0] is (" << arg0 << ")\n";
	// I don't use the argument for anything, but potentially could have arguments
	// to get fancy with options.
	cout << "scanning directory \"" << testdir << '\"' << '\n';
	for(auto& p : fs::recursive_directory_iterator(testdir)) {
//		if (!p.is_regular_file()) continue;
		if (p.status().type() != fs::file_type::regular)  continue;
		fs::path fname{p};
		if (fname.extension() != ".cpp")  continue;
		// lexically_relative is not present in MS's header.
		fname= relative_name(fname);
		auto folder= fname.parent_path();
		auto local= fname.filename();
		cout << '(' << folder << ")  ";
		cout << '(' << local << ")  ";
		cout << fname << '\n';
		process (move(folder), local.stem());
	}
	write_sln();
	return 0;
}