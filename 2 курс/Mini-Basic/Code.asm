include\masm32\include\masm32rt.inc

.386
	.data?

	M dd ?
	N dd ?
	X dd ?
	R0 dd ?
	C1 dd ?
	R1 dd ?
	T1 dd ?
	C2 dd ?
	T2 dd ?
	T3 dd ?

	.data

	temp307 dd 0
	temp308 dd 0
	temp309 dd 0
	temp310 dd 0
	temp311 dd 0
	temp312 dd 0
	temp313 dd 0
	temp314 dd 0
	temp315 dd 0

	.code
	start:
	 call label_10
	 print str$(R0),10,13
	 print str$(R1),10,13
	 exit
	label_10 proc 
		mov eax, 5
		mov N, eax
		call label_20
		ret
	label_10 endp
	label_20 proc 
		mov eax, 6
		mov M, eax
		call label_30
		ret
	label_20 endp
	label_30 proc 
		mov eax, 1
		mov X, eax
		call label_31
		ret
	label_30 endp
	label_31 proc 
		mov eax, 0
		mov C1, eax
		call label_32
		ret
	label_31 endp
	label_32 proc 
		mov eax, 0
		mov C2, eax
		call label_40
		ret
	label_32 endp
	label_40 proc 
		mov eax, X
		cmp eax, N
		JS label_80
		call label_50
		ret
	label_40 endp
	label_50 proc 
		mov eax, 1
		mov X, eax
		call label_60
		ret
	label_50 endp
	label_60 proc 
		mov eax, X
		cmp eax, M
		JS label_180
		call label_70
		ret
	label_60 endp
	label_70 proc 
		call label_5000
		call label_80
		ret
	label_70 endp
	label_80 proc 
		mov eax, X
		mov T1, eax
		call label_81
		ret
	label_80 endp
	label_81 proc 
		mov eax, 0
		mov T2, eax
		call label_82
		ret
	label_81 endp
	label_82 proc 
		mov eax, 0
		mov T3, eax
		call label_90
		ret
	label_82 endp
	label_90 proc 
		mov eax, T1
		cmp eax, 0
		JE label_120
		call label_91
		ret
	label_90 endp
	label_91 proc 
		mov eax, T1
		mov ebx, 10
		div ebx
		mov temp307, eax
		mov eax, temp307
		mov T3, eax
		call label_92
		ret
	label_91 endp
	label_92 proc 
		mov eax, T3
		mov ebx, 10
		mul ebx
		mov temp308, eax
		mov eax, temp308
		mov T3, eax
		call label_93
		ret
	label_92 endp
	label_93 proc 
		mov eax, T1
		mov ebx, 10
		div ebx
		mov temp309, eax
		mov eax, temp309
		mov T1, eax
		call label_100
		ret
	label_93 endp
	label_100 proc 
		mov eax, T2
		add eax, T3
		mov temp310, eax
		mov eax, temp310
		mov T2, eax
		call label_110
		ret
	label_100 endp
	label_110 proc 
		call label_90
		call label_120
		ret
	label_110 endp
	label_120 proc 
		mov eax, T2
		cmp eax, N
		JNE label_140
		call label_130
		ret
	label_120 endp
	label_130 proc 
		mov eax, 1
		mov C1, eax
		call label_140
		ret
	label_130 endp
	label_140 proc 
		call label_40
		call label_180
		ret
	label_140 endp
	label_180 proc 
		mov eax, X
		mov T1, eax
		call label_181
		ret
	label_180 endp
	label_181 proc 
		mov eax, 0
		mov T2, eax
		call label_182
		ret
	label_181 endp
	label_182 proc 
		mov eax, 0
		mov T3, eax
		call label_190
		ret
	label_182 endp
	label_190 proc 
		mov eax, T1
		cmp eax, 0
		JE label_120
		call label_191
		ret
	label_190 endp
	label_191 proc 
		mov eax, T1
		mov ebx, 10
		div ebx
		mov temp311, eax
		mov eax, temp311
		mov T3, eax
		call label_192
		ret
	label_191 endp
	label_192 proc 
		mov eax, T3
		mov ebx, 10
		mul ebx
		mov temp312, eax
		mov eax, temp312
		mov T3, eax
		call label_193
		ret
	label_192 endp
	label_193 proc 
		mov eax, T1
		mov ebx, 10
		div ebx
		mov temp313, eax
		mov eax, temp313
		mov T1, eax
		call label_1100
		ret
	label_193 endp
	label_1100 proc 
		mov eax, T2
		add eax, T1
		mov temp314, eax
		mov eax, temp314
		sub eax, T3
		mov temp315, eax
		mov eax, temp315
		mov T2, eax
		call label_1110
		ret
	label_1100 endp
	label_1110 proc 
		call label_90
		call label_1120
		ret
	label_1110 endp
	label_1120 proc 
		mov eax, T2
		cmp eax, M
		JNE label_140
		call label_1130
		ret
	label_1120 endp
	label_1130 proc 
		mov eax, 1
		mov C2, eax
		call label_1140
		ret
	label_1130 endp
	label_1140 proc 
		call label_60
		call label_5000
		ret
	label_1140 endp
	label_5000 proc 
		mov eax, C1
		mov R0, eax
		call label_5001
		ret
	label_5000 endp
	label_5001 proc 
		mov eax, C2
		mov R1, eax
		call label_5002
		ret
	label_5001 endp
	label_5002 proc 
	label_5002 endp
end start
