def transform_list(part_list): #transforming list form
    Liste = []
    for i in range(len(part_list)):
        Liste.append([])
        for k in range(len(part_list[i])):
            if type(part_list[i][k]) == tuple:
                Liste[-1].append(list(part_list[i][k]))
            else:
                Liste[-1].append(part_list[i][k])
    return Liste

def searching_nodes(Liste,item): #inserting nodes into tree
    for i in range(len(Liste)):
        if type(Liste[i]) == list:
            searching_nodes(Liste[i],item)
        elif Liste[i]== item[0]:
                Liste += item[1:]

def sorting_list(queue):
    flat = []
    root = None
    for k in range(len(queue)):
        for i in range(len(queue[k])):
            if type(queue[k][i])==list:
                for j in range(len(queue[k][i])):
                    if type(queue[k][i][j])== str:
                        flat.append(queue[k][i][j])        
            elif type(queue[k][i]) == str:
                flat.append(queue[k][i])
    for i in flat:
        a = flat.count(i)
        if a ==1:
            root = i
    #print(root)
    for i in range(len(queue)):
        if queue[i][0]==root:
            queue = queue[:i]+ queue[i+1:]+ [queue[i]]
    return queue
            
def create_tree(part_list): #creating tree completely
    part_list = transform_list(part_list)
    queue = sorting_list(part_list)
    #print(queue)
    while len(queue)>1:
        item = queue.pop(0)
        searching_nodes(queue,item)
    return [1] + queue[0] 
        
def calculate_price(part_list):
    part_list = create_tree(part_list)
    price = [0]
    def calculate_price_helper(part_list_new,number):
        if type(part_list_new[-1]) == float:
            price[0] += number*part_list_new[0]*part_list_new[-1]
        else:
            for i in part_list_new[2:]:
                calculate_price_helper(i,part_list_new[0]*number)
        return price[0]
    return calculate_price_helper(part_list,1)

def required_parts(part_list):
    part_list = create_tree(part_list)
    required_list = []
    def required_parts_helper(part_list,time):
        total = time
        number = part_list[0]
        children = part_list[2:]
        if type(part_list[-1]) == float:
            total *= number
            required_list.append((int(total),part_list[1]))
        else:
            total *= number
            for i in children:
                #print(total,i)
                required_parts_helper(i,total)
        return required_list
    return required_parts_helper(part_list,1)

def stock_check(part_list,stock_list):
    required_list_new = required_parts(part_list)
    required_stock = []
    while required_list_new:
        item = required_list_new.pop(0)
        occur = False
        for j in range(len(stock_list)):
            r_number = item[0]
            r_item = item[1]
            s_number = stock_list[j][0]
            s_item = stock_list[j][1]            
            if r_item == s_item:
                if r_number > s_number :
                    number =  r_number - s_number
                    required_stock.append((r_item,number))
                occur= True       
        if occur == False:
            required_stock.append((item[1],item[0]))
    return required_stock

#print(required_parts(L))
#print(stock_check(L,s))
#print(calculate_price(L))