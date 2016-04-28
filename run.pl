#########################################################################
#
# If the target platform is managed AND /Za is specified, cause the test
#   to skip (/clr and /Za are incompatible).
#
#  --arjunb 9/22/03
#
#########################################################################
if($ENV{TARGET_IS_MANAGED} == 1 && $ENV{CFLAGS} =~ /[-\/]Za/)
{
	print "SKIPPED: /clr and /Za are incompatible.\n";
	exit(2);
}



$src = $ENV{SOURCE};
$switches = $ENV{CFLAGS};
$otherswitches = $ENV{OTHERSWITHCES};
if ($ENV{COMPILE_ONLY} == 1) {
	$c = "-c";
}
	

#compile source file
print("cl $c $switches $otherswitches $compile_only $src $src2 -Fetest.exe\n");
$ret = system("cl $c $switches $otherswitches  -Fetest.exe $src $src2")>>8;
if ($ret != 0) {
	print("compile $src failed\n");
	exit(1);
}

if ($ENV{COMPILE_ONLY}==1) {
	print("Passed\n");
	exit(0);
}

#execute
print("$ENV{SIMULATOR_PIPE} test.exe\n");
$ret = system("$ENV{SIMULATOR_PIPE} test.exe")>>8;
if ($ret != 0) {
	print("Execute test.exe failed\n");
	exit(1);
}

print("Passed\n");
exit(0); 
	


    
