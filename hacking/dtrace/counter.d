dtrace:::BEGIN
{
	i = 0;
}

profile:::tick-1sec
{
	i = i + 1;
	printf("Currently at %d", i);
}

profile:::tick-1sec
/i==5/
{
	exit(0);
}
