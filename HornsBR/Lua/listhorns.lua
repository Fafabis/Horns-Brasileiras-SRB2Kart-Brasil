local function listhorns_kbr(player, index)
    local horns = HORNMOD_Horns()
    local horn_count = #horns
    if tonumber(index) == nil then
        index = 0
    else
        index = tonumber(index) - 1
        if 300 + (index*20) > horn_count then
            index = 0
        end
    end
    local start = 301 + (index*20)
    local upper_limit = start + 19
    if upper_limit > horn_count then
		upper_limit = horn_count
	end
    local horns_br = horn_count - 300
    CONS_Printf(player,"--- Pagina \136" + (index+1) + " \128de \136" + (horns_br/20 + (horns_br % 20 and 1 or 0)) + " \128---")
    for number = start, upper_limit do
        CONS_Printf(player,"\131" + number + ". \130" + horns[number].info)
    end
    CONS_Printf(player,"Experimente usar \131listhorns \130[pagina]\128, \131sethorn \130[numero] \128ou \131sethorn \130[palavra]\128!")
end

COM_AddCommand("listhorns", listhorns_kbr)
