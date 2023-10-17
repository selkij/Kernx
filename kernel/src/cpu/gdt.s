.global set_gdtr

set_gdtr:
    lgdt (%rdi)
    retq