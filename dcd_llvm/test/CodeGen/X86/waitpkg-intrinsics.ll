; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-linux -mattr=+waitpkg | FileCheck %s --check-prefix=X64
; RUN: llc < %s -mtriple=i386-pc-linux -mattr=+waitpkg | FileCheck %s --check-prefix=X32

define void @test_umonitor(i8* %address) {
; X64-LABEL: test_umonitor:
; X64:       # %bb.0: # %entry
; X64-NEXT:    umonitor %rdi
; X64-NEXT:    retq
;
; X32-LABEL: test_umonitor:
; X32:       # %bb.0: # %entry
; X32-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X32-NEXT:    umonitor %eax
; X32-NEXT:    retl
entry:
  call void @llvm.x86.umonitor(i8* %address)
  ret void
}

define i8 @test_umwait(i32 %control, i32 %counter_high, i32 %counter_low) {
; X64-LABEL: test_umwait:
; X64:       # %bb.0: # %entry
; X64-NEXT:    movl %edx, %eax
; X64-NEXT:    movl %esi, %edx
; X64-NEXT:    umwait %edi
; X64-NEXT:    setb %al
; X64-NEXT:    retq
;
; X32-LABEL: test_umwait:
; X32:       # %bb.0: # %entry
; X32-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X32-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X32-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X32-NEXT:    umwait %ecx
; X32-NEXT:    setb %al
; X32-NEXT:    retl
entry:
  call i8 @llvm.x86.umwait(i32 %control, i32 %counter_high, i32 %counter_low)
  ret i8 %0
}

define i8 @test_tpause(i32 %control, i32 %counter_high, i32 %counter_low) {
; X64-LABEL: test_tpause:
; X64:       # %bb.0: # %entry
; X64-NEXT:    movl %edx, %eax
; X64-NEXT:    movl %esi, %edx
; X64-NEXT:    tpause %edi
; X64-NEXT:    setb %al
; X64-NEXT:    retq
;
; X32-LABEL: test_tpause:
; X32:       # %bb.0: # %entry
; X32-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X32-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X32-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X32-NEXT:    tpause %ecx
; X32-NEXT:    setb %al
; X32-NEXT:    retl
entry:
  call i8 @llvm.x86.tpause(i32 %control, i32 %counter_high, i32 %counter_low)
  ret i8 %0
}

declare void @llvm.x86.umonitor(i8*)
declare i8 @llvm.x86.umwait(i32, i32, i32)
declare i8 @llvm.x86.tpause(i32, i32, i32)