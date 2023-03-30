#ifndef ZAPR_H
#define ZAPR_H

#define LEN 1234

//#define OTL

//#define OTLSLO

//define SECOND

#include <stdio.h>
#include <string.h>

enum class zapr_uslo
{
	err,
	all,
	one,	
};

enum class zapr_simb
{
	err,
	pod,//podcherk
	proc,//procent
	sko,//skobki
	unsk,//[^...]
};

void portim(char* word, zapr_simb task);

int chek12(char* str1, char* str2);

int chek34(char* str1, char* str2);

int chek5(char* str1, char* str2);

int chek6(char* str1, char* str2);



int chek12(char* str1, char* str2)
{
	int i = 0;
	for(i = 0; str1[i] && str1[i] == str2[i];i++);
	
	if(!str2[i])
	{
		if(!str1[i])
		{
			return 1;
		}
		return 0;
	}else
	{
		if(!str1[i])
		{
			return 0;
		}
	}
		
	
	if(str2[i] == '\n')
		return chek12(str1+i+1, str2+i+1);
	return 0;
}

int chek34(char* str1, char* str2)
{
	int i = 0;
	for(i = 0; str1[i] && str1[i] == str2[i];i++);
	
	if(!str2[i])
	{
		if(!str1[i])
		{
			return 1;
		}
		return 0;
	}else
	{
		if(!str1[i])
		{
			if(str2[i]=='\n')
				return 1;
			return 0;
		}
	}
	
	if(str2[i] == '\n')
	{
		if(chek34(str1+i+1, str2+i+1))//2
			return 1;
		if(chek34(str1+i, str2+i+1))//1
			return 1;
		if(chek34(str1+i+1, str2+i))//3
			return 1;
	}
	return 0;
}

int chek5(char* str1, char* str2)
{
	int i = 0;
	for(i = 0; str1[i] && str1[i] == str2[i];i++);
	#ifdef OTL
	printf("%s %s\n", str1+i, str2+i);
	#endif
	if(!str2[i])
	{
		if(!str1[i])
		{
			return 1;
		}
		return 0;
	}else
	{
		if(!str1[i])
		{
			return 0;
		}
	}
	
	if(str2[i] == '\n')
	{
		if(str2[i+1] && (str1[i] >= str2[i+1]) && str2[i+2] && str2[i+3] && (str2[i+3] >= str1[i]))
		{
			return chek5(str1+i+1, str2+i+4);
		}
		return 0;
	}
	return 0;
}

int chek6(char* str1, char* str2)
{
	int i = 0;
	for(i = 0; str1[i] && str1[i] == str2[i];i++);
	

	if(!str2[i])
	{
		if(!str1[i])
		{
			return 1;
		}
		return 0;
	}else
	{
		if(!str1[i])
		{
			return 0;
		}
	}
	
	if(str2[i] == '\n')
	{
		if(str2[i+1] && str2[i+2] && str2[i+3] && ((str2[i+3] < str1[i]) || (str1[i] < str2[i+1])))
		{
			return chek6(str1+i+1, str2+i+4);
		}
		return 0;
	}
	return 0;
}

class zapr
{
private:
	zapr_uslo cond = zapr_uslo::err;
	zapr_simb simbol = zapr_simb::err;

	char* find[LEN/2];
	char* tabs = nullptr;
public:

	int real(FILE* in, FILE* out)
	{
		char buf[LEN];
		char vsp[LEN];
		int counter = 0;
		int i = 0;
		int fl = 0;
		int res = 0;
		char* tekword = nullptr;
		char* hvost = nullptr;
		while(fgets(buf, LEN, in))
		{
			res = 0;

			for(i = 0; i < LEN && buf[i]; i++)
			{
				if(buf[i] == '\n')
				{
					buf[i] = '\0';
					vsp[i] = '\0';
				}
				else
				{
					vsp[i] = buf[i];					
				}
			
			}
			vsp[i] = '\0';
			#ifdef OTL
			printf("!!!!!!%s!!!!!!\n", vsp);
			#endif
			switch (simbol)
			{
				case zapr_simb::err:
					return 0;
				case zapr_simb::pod:
						//1 2
						fl = 0;
						hvost = nullptr;
						tekword = strtok_r(vsp, tabs, &hvost);
						if(cond == zapr_uslo::one)
						{
							if(tekword)
							{
								#ifdef OTL
								printf("tekword = \'%s\'\n", tekword);
								#endif
								for(i = 0; i < LEN/2 && find[i] && !fl; i++)
								{
									if(chek12(tekword, find[i]))
									{
										#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
											res = 1;
									}
								}

								while((tekword = strtok_r(nullptr, tabs, &hvost)) && !res)
								{
									fl = 0;
									#ifdef OTL
									printf("tekword = \'%s\'\n", tekword);
									#endif
									for(i = 0; i < LEN/2 && find[i] && !fl; i++)
									{
										if(chek12(tekword, find[i]))
										{
											res = 1;
											#ifdef OTL
											printf("\'%s\' DA\n", tekword);
											#endif
										}
									}
								}
							}else
							{
								res = 0;/////////////////////////////////////////////////
							}
						}else
						{
							if(tekword)
							{
								#ifdef OTL
								printf("tekword = \'%s\' find[0] = \'%s\':%d\n", tekword, find[0],chek12(tekword, find[0]));
								#endif
								if(chek12(tekword, find[0]))
								{
									res = 1;
									#ifdef OTL
									printf("\'%s\' DA\n", tekword);
									#endif

								}
								
								
								fl = 0;
								i = 0;
								while((tekword = strtok_r(nullptr, tabs, &hvost))&& !fl && res)
								{
									fl = 0;

									i++;
									#ifdef OTL
									printf("tekword = \'%s\' find[%d] = \'%s\'\n", tekword, i, find[i]);
									#endif
									if(!find[i])
									{
										fl = 1;
									}
									if(!fl && !chek12(tekword, find[i]))
									{
										res = 0;
										#ifdef OTL
										printf("\'%s\' NET\n", tekword);
										#endif
									}
								}
							}else
							{
								res = 1;
							}
						}
						break;
				case zapr_simb::proc:
						fl = 0;
						hvost = nullptr;
						tekword = strtok_r(vsp, tabs, &hvost);
						if(cond == zapr_uslo::one)
						{
							if(tekword)
							{
								#ifdef OTL
								printf("tekword = \'%s\'\n", tekword);
								#endif
								for(i = 0; i < LEN/2 && find[i] && !fl; i++)
								{
									if(chek34(tekword, find[i]))
									{
										#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
											res = 1;
									}
								}

								while((tekword = strtok_r(nullptr, tabs, &hvost)) && !res)
								{
									fl = 0;
									#ifdef OTL
									printf("tekword = \'%s\'\n", tekword);
									#endif
									for(i = 0; i < LEN/2 && find[i] && !fl; i++)
									{
										if(chek34(tekword, find[i]))
										{
											res = 1;
											#ifdef OTL
											printf("\'%s\' DA\n", tekword);
											#endif
										}
									}
								}
							}else
							{
								res = 0;/////////////////////////////////////////////////
							}
						}else
						{
							if(tekword)
							{
								#ifdef OTL
								printf("tekword = \'%s\' find[0] = \'%s\':%d\n", tekword, find[0],chek12(tekword, find[0]));
								#endif
								if(chek34(tekword, find[0]))
								{
									res = 1;
									#ifdef OTL
									printf("\'%s\' DA\n", tekword);
									#endif

								}
								
								
								fl = 0;
								i = 0;
								while((tekword = strtok_r(nullptr, tabs, &hvost))&& !fl && res)
								{
									fl = 0;

									i++;
									#ifdef OTL
									printf("tekword = \'%s\' find[%d] = \'%s\'\n", tekword, i, find[i]);
									#endif
									if(!find[i])
									{
										fl = 1;
									}
									if(!fl && !chek34(tekword, find[i]))
									{
										res = 0;
										#ifdef OTL
										printf("\'%s\' NET\n", tekword);
										#endif
									}
								}
							}else
							{
								res = 1;
							}
						}
						break;
				case zapr_simb::sko:
						fl = 0;
						hvost = nullptr;
						tekword = strtok_r(vsp, tabs, &hvost);

						if(tekword)
						{
							#ifdef OTL
							printf("tekword = \'%s\'\n", tekword);
							#endif
							for(i = 0; i < LEN/2 && find[i] && !fl; i++)
							{
								if(chek5(tekword, find[i]))
								{
									fl = 1;
									#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
									if(cond == zapr_uslo::one)
										res = 1;

								}
							}
							if(!fl && cond == zapr_uslo::all)
								res = 0;
							while((tekword = strtok_r(nullptr, tabs, &hvost)))
							{
								fl = 0;
								#ifdef OTL
								printf("tekword = \'%s\'\n", tekword);
								#endif
								for(i = 0; i < LEN/2 && find[i] && !fl; i++)
								{
									if(chek5(tekword, find[i]))
									{
										fl = 1;
										#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
										if(cond == zapr_uslo::one)
											res = 1;

									}
								}
								if(!fl && cond == zapr_uslo::all)
									res = 0;
							}
						}else
						{
							res = 0;/////////////////////////////////////////////////
						}
						break;
				case zapr_simb::unsk:
						fl = 0;
						hvost = nullptr;
						tekword = strtok_r(vsp, tabs, &hvost);

						if(tekword)
						{
							#ifdef OTL
							printf("tekword = \'%s\'\n", tekword);
							#endif
							for(i = 0; i < LEN/2 && find[i] && !fl; i++)
							{
								if(chek6(tekword, find[i]))
								{
									fl = 1;
									#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
									if(cond == zapr_uslo::one)
										res = 1;

								}
							}
							if(!fl && cond == zapr_uslo::all)
								res = 0;
							while((tekword = strtok_r(nullptr, tabs, &hvost)))
							{
								fl = 0;
								#ifdef OTL
								printf("tekword = \'%s\'\n", tekword);
								#endif
								for(i = 0; i < LEN/2 && find[i] && !fl; i++)
								{
									if(chek6(tekword, find[i]))
									{
										fl = 1;
										#ifdef OTL
										printf("\'%s\' DA\n", tekword);
										#endif
										if(cond == zapr_uslo::one)
											res = 1;

									}
								}
								if(!fl && cond == zapr_uslo::all)
									res = 0;
							}
						}else
						{
							res = 0;/////////////////////////////////////////////////
							
						}
						break;
			}
			if(res)
			{
				counter++;
				fprintf(out, "%s\n", buf);
			}
		}
		return counter;
	}

	zapr()
	{
		int i = 0;
		for(i = 0; i < LEN/2; i++)
		{
			find[i] = nullptr;
		}
	}

	

	void kraft(int nom, char* s, char* t)
	{
		switch (nom)
		{
			case 1: cond = zapr_uslo::one;
					simbol = zapr_simb::pod;
					break;
			case 2: cond = zapr_uslo::all;
					simbol = zapr_simb::pod;
					break;
			case 3: cond = zapr_uslo::one;
					simbol = zapr_simb::proc;
					break;
			case 4: cond = zapr_uslo::all;
					simbol = zapr_simb::proc;
					break;
			case 5: cond = zapr_uslo::one;
					simbol = zapr_simb::sko;
					break;
			case 6: cond = zapr_uslo::one;
					simbol = zapr_simb::unsk;
					break;
			default:
				return;
		}
		char* hvost = nullptr;
		tabs = t;
		find[0] = strtok_r(s, t, &hvost);
		int i = 0;
		for(i = 1; (find[i] = strtok_r(nullptr, t, &hvost))!= nullptr; i++);

		for(i = 0; find[i]; i++)
		{
			portim(find[i], simbol);
		}
		#ifdef OTLSLO
		for(i = 0; i < LEN/2 && find[i]; i++)
		{
			printf("find[%d] = \'%s\'\n", i, find[i]);
		}
		#endif
	}



	~zapr() = default;
	
};

void portim(char* word, zapr_simb task)
{
	int i = 0, j = 0, fl = 0;
	char si = 0;
	switch(task)
	{
		case zapr_simb::pod: si = '_';
		break;
		case zapr_simb::proc: si = '%';
		break;
		default: si = '[';
	}
//	printf("s = %s\n", word);
	for(i = 0; word[i]; i++)
	{
		if(word[i]=='\\' && !fl)
		{
			fl = 1;
		}else
		{
			if(fl)
			{
				word[j] = word[i];
				j++;
			}else
			{
				if(word[i] == si)
				{
					word[j] = '\n';
					j++;
					if(task == zapr_simb::unsk)
					{
						i++;
					}
					if(task == zapr_simb::unsk || task == zapr_simb::sko)
					{
					//	i++;
						for(int k = 0; k < 3; k++)
						{

							i++;
						/*	if(!word[i])
							{
								word[j] = '\0';
								return;
							}*/
							word[j] = word[i];//cpy n-m
							j++;
						}
						i++;
					}
				}else
				{
					word[j++] = word[i];
				}
			}
			fl = 0;
		}
	}
	word[j] = '\0';
	#ifdef OTLSLO
	printf("!!word = \'%s\'\n", word);
	#endif
}

#endif