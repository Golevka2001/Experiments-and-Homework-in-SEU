global addrToAgent : table[addr] of set[string] = table();

event http_header (c: connection, is_orig: bool, name: string, value: string)
	{
	if ( c$http?$user_agent )
		{
		local src_ip = c$id$orig_h;
		local user_agent = to_lower(c$http$user_agent);
		if (src_ip in addrToAgent)
			{
			add(addrToAgent[src_ip])[user_agent];
			}
		else
			{
			addrToAgent[src_ip] = set(user_agent);
			}
		}
	}

event zeek_done()
	{
	for (addr_ip in addrToAgent)
		{
		if (|addrToAgent[addr_ip]| >= 3)
			{
			print fmt("%s is a proxy", addr_ip);
			}
		}
	}
