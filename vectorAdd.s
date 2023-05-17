.globl vectorAdd
vectorAdd:
  pushl %ebp
  movl %esp, %ebp
  pushl %ecx
  pushl %ebx
  pushl %edi
  movl 8(%ebp), %ecx      
  movl 12(%ebp), %ebx     
  movl 16(%ebp), %edi    
  clc 
                    
vector_add:
  movb (%ebx,%edi), %al  
  adc %al, (%ecx,%edi)   
  decl %edi
  jns vector_add               
  jnc end
carry:
  dec %ecx
  incb (%ecx)
  je carry  
end:
  popl %edi
  popl %ebx
  popl %ecx
  popl %ebp
  ret
  