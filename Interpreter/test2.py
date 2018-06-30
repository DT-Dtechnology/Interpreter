# -*- coding: UTF-8 -*-
PI = 3

def calculate_circle(r): # 简单的函数调用
	result = PI
	for i in range(3): # for循环
		result = result * r
	return result

def main():
	print "Calculate the area of shape:"
	
	# Step 1: Circle
	print "Circle"
	for i in range(3,8): # for循环
		print "Radius: %d, area: %d" % (i, calculate_circle(i)) # 控制格式的输出

	# Step 2: Rectangle
	print "Rectangle"
	len_st, len_en = 2, 4 # 逗号
	wid_st, wid_en = 1, 2
	ptr_len, ptr_wid = len_st, wid_st
	step = 1
	while (ptr_len <= len_en) and (ptr_wid <= wid_en): # while循环
		print "Length: %d, width: %d, area: %d" % (ptr_len, ptr_wid, ptr_len * ptr_wid) # 控制格式的输出
		ptr_wid = ptr_wid + step
		if (ptr_wid > wid_en): # if分支语句
			ptr_len, ptr_wid = ptr_len + step, wid_st

main()
a = 3

