.name "aff"
.comment "let's meeow"

sti    r1, %:live, %1            #change live by the right value
sti    r1, %:live2, %1            #change live by the right value
ld    %1, r3
ld    %33, r6
ld    %77, r7
aff		r7
ld    %97, r7
aff		r7
ld    %111, r7
aff		r7
aff		r7
ld    %119, r7
aff		r7
ld    %0, r7
aff		r7

#While (r2 < 10)
forks:
add    r2, r3, r2        #increment r2
xor    r2, %15, r4        #if (r4) {carry = 0}
live2:
live     %4
zjmp    %:endwhile        #if (carry)
ld    %0, r4            #carry = 1
zjmp    %:forks
#EndWhile
endwhile:
ld    %0, r4            #carry = 1

live:
live %4
zjmp %:live
