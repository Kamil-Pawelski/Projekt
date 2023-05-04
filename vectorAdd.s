.globl vectorAdd
vectorAdd:
  pushl %ebp
  movl %esp, %ebp
  pushl %edi
  clc 
  movl 8(%ebp), %ecx      
  movl 12(%ebp), %edx     
  movl 16(%ebp), %edi                        
vector_add:
  movb (%edx,%edi), %al  
  adc %al, (%ecx,%edi)   
  decl %edi
  jns vector_add               
  jnc end
  dec %ecx
  incb (%ecx)
end:
  popl %edi
  popl %ebp
  ret
  