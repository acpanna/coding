#!/usr/bin/perl

$isdnlog = "/var/log/isdn.log";

print "|---|| Internetnutzung ||---|";
print "\n\r\n\r";
print "[ T-Online ]\n\r";
calculate("+49191011");
print "\n\r";
print "[ FreeNet ]\n\r";
calculate("+4919231777");

sub calculate 
{
	my ($provider, $line, $mins, $hours, $allmins, $allhours);
	my (@result, @splitted, @key);
	my (%hash);
			
	$provider = $_[0];
	@result = `grep "+499273264      |$provider" $isdnlog | sed -e "s/[0-9][0-9]:.\\{44\\}//" -e "s/|.\\{10\\}|.*//"`;

	$i=0;
	for $line (@result) {
		@splitted = split(/\|/, $line);

		if (! exists $hash{"$splitted[0]"}) {
			$key[$i] = "$splitted[0]";
			$i++;
		}
		
		$hash{"$splitted[0]"} += $splitted[1];
	}

	for ($i=0; $i<=$#key; $i++) {
		$mins     = $hash{"$key[$i]"} / 60;
	  	$allmins += $mins;
		$hours    = $mins / 60;
		@splitted = split(/\./, $hours);
		$hours    = @splitted[0];
		$mins     = $mins - 60 * $hours;
		@splitted = split(/\./, $mins);
		$mins     = @splitted[0];

		print "  $key[$i]: ".$hours."h ".$mins."m\n\r";
	}

	$allhours = $allmins / 60;
	@splitted = split(/\./, $allhours);
	$allhours = @splitted[0];
	$allmins  = $allmins - $allhours * 60;
	@splitted = split(/\./, $allmins);
	$allmins  = @splitted[0];

	print "Gesamt: ".$allhours."h ".$allmins."m\n\r";
}
