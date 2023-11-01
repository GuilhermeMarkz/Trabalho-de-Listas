Letra* retorna_Letra_bychar(char letra)
{
    int i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		if (letra == LetraAux->letra)
		{
			return LetraAux;
		}
		LetraAux = LetraAux->next;
		i++;
	}

	return NULL;
}
