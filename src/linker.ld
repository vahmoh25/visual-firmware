SECTIONS
{
    .text 0x10000000 : {
        *(.vector_table)
        *(.image_def)
    }
}
