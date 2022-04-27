; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=i686-linux          | FileCheck %s --check-prefix=X32
; RUN: llc < %s -mtriple=x86_64-linux        | FileCheck %s --check-prefix=X64
; RUN: llc < %s -mtriple=x86_64-linux-gnux32 | FileCheck %s --check-prefix=X64
; RUN: llc < %s -mtriple=x86_64-nacl         | FileCheck %s --check-prefix=X64

; The computation of %t4 should match a single lea, without using actual add instructions.

define i32 @test1(i32 %A, i32 %B) {
; X32-LABEL: test1:
; X32:       # %bb.0:
; X32-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X32-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X32-NEXT:    leal -5(%ecx,%eax,4), %eax
; X32-NEXT:    retl
;
; X64-LABEL: test1:
; X64:       # %bb.0:
; X64-NEXT:    # kill: def $esi killed $esi def $rsi
; X64-NEXT:    # kill: def $edi killed $edi def $rdi
; X64-NEXT:    leal -5(%rsi,%rdi,4), %eax
; X64-NEXT:    retq
  %t1 = shl i32 %A, 2
  %t3 = add i32 %B, -5
  %t4 = add i32 %t3, %t1
  ret i32 %t4
}

