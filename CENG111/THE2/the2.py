#
# WRITE YOUR CODE HERE AND SEND ONLY THIS FILE TO US.
#
# DO NOT DEFINE get_data() here. Check before submitting
#[M, N,   D,   K, LAMBDA, MU,    universal_state]

import math
import random
from evaluator import *    # get_data() will come from this import

Data=get_data()
M = Data[0]
N = Data[1]
D=Data[2]
K=Data[3]
Lambda=Data[4]
Mu=Data[5]
universal_state=Data[6]

def new_positions_helper(t,l_m):
	global M
	global N
	t_new=list(t)
	if l_m==0:
		t_new[1] += 1
	elif l_m==1:
		t_new[0] -= 1
		t_new[1] += 1
	elif l_m==2:
		t_new[0] -= 1
	elif l_m==3:
		t_new[0] -= 1
		t_new[1] -= 1
	elif l_m==4:
		t_new[1] -=1
	elif l_m==5:
		t_new[0] +=1
		t_new[1] -=1
	elif l_m==6:
		t_new[0] +=1
	elif l_m==7:
		t_new[0] += 1
		t_new[1] += 1
	if t_new[0] >= N or t_new[1]>= M:
		return t,l_m
	elif t_new[0]<0 or t_new[1]<0:
		return t,l_m
	else:
		return (tuple(t_new),l_m)

def new_positions(t,l_m):
	global Mu
	green = (1 / 2) * (Mu) #Forward
	yellow = (1 / 8) * (Mu) #Forward Left-Right
	blue = (1 / 2) * (1 - Mu - Mu ** 2) #Left-Right
	purple = (2 / 5) * (Mu ** 2) #Backward Left-Right
	gray = (1 / 5) * (Mu ** 2) #Backward
	if l_m==0:
		last_move_list = [0, 1, 2, 3, 4, 5, 6, 7]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list,weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==1:
		last_move_list = [1, 2, 3, 4, 5, 6, 7,0]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==2:
		last_move_list = [2, 3, 4, 5, 6, 7, 0, 1]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==3:
		last_move_list = [3, 4, 5, 6, 7, 0, 1, 2]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==4:
		last_move_list = [4, 5, 6, 7,0, 1, 2, 3]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==5:
		last_move_list = [5, 6, 7, 0, 1, 2, 3, 4]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==6:
		last_move_list = [6, 7, 0, 1, 2, 3, 4, 5]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New
	elif l_m==7:
		last_move_list = [7, 0, 1, 2, 3, 4, 5, 6, ]
		weights_list = [green,yellow,blue,purple,gray,purple,blue,yellow]
		l_m_new = random.choices(last_move_list, weights=weights_list)[0]
		New =  new_positions_helper(t,l_m_new)
		if New[0]==t:
			return (t,l_m)
		else:
			return New

def get_infected(first,second,distance):
	#checking infection
	global Lambda
	global K
	Pij= min(1,K/distance**2)
	infection_status_list = ["infected", "notinfected"]
	infection_sit= None
	if first[2] == "masked" and second[2] == "masked":
		Pij = Pij / (Lambda ** 2)
		infection_sit = random.choices(infection_status_list, weights=[Pij, 1 - Pij])
	elif first[2]=="masked" and second[2]=="notmasked":
		Pij = Pij / Lambda
		infection_sit = random.choices(infection_status_list, weights=[Pij, 1 - Pij])
	elif first[2] == "notmasked" and second[2] == "masked":
		Pij= Pij / Lambda
		infection_sit = random.choices(infection_status_list, weights=[Pij, 1 - Pij])
	elif first[2] == "notmasked" and second[2]=="notmasked":
		Pij = Pij
		infection_sit=random.choices(infection_status_list,weights=[Pij,1-Pij])
	return infection_sit

def new_move():
	# write here your definition. You can also define helper functions
	global universal_state
	global D
	# universal_state=[location,last_move,mask_status,infection_status]
	#print(universal_state)
	location_list = [loc[0] for loc in universal_state]
	for i in range(len(universal_state)):
		#changing positions
		new_position_data = new_positions(universal_state[i][0],universal_state[i][1])
		#new_position_data returns new (x,y) and last_move
		#print(new_position_data,location_list)
		if new_position_data[0] in location_list:
			continue
		else:
			universal_state[i][0] = new_position_data[0]
			universal_state[i][1] = new_position_data[1]
		location_list[i] = new_position_data[0]
	copy_universal_state = [ x[:] for x in universal_state]
	for i in range(len(copy_universal_state)):
			for j in range(i+1,len(copy_universal_state)):
				location_1 = copy_universal_state[i][0]
				location_2 = copy_universal_state[j][0]
				x_1 = location_1[0]
				y_1 = location_1[1]
				x_2 = location_2[0]
				y_2 = location_2[1]
				distance = ((y_2 - y_1) ** 2 + (x_2 - x_1) ** 2) ** (1 / 2)
				if copy_universal_state[i][3] != copy_universal_state[j][3]:
					#print("dis",distance)
					if distance <= D:
						# checking distance between individuals
						infection_sit = get_infected(copy_universal_state[i],copy_universal_state[j],distance)
						#print(infection_sit)
						if infection_sit == ["infected"]:
							#print(universal_state[i][3])
							if copy_universal_state[i][3]=="notinfected":
								universal_state[i][3]="infected"
							elif copy_universal_state[j][3]=="notinfected":
								universal_state[j][3]="infected"
	return universal_state