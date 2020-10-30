int sam_mmap_entry(const char *path ,off_t size ,int prot ,int flag)
{
    mmaps->fd = open(path, O_WONLY);
    if(mmaps->fd < 0){
        goto err_exit;
    }

    if(fstat(mmaps->fd ,&mmaps->st) != sam_suc){
        goto err_close;
    } 

    if(!(mmaps->st.st_size)){
        goto err_close;
    }

    if(size != mmap_invalid_size){
        mmaps->st.st_size = size;
    }

    mmaps->ptr = mmap(NULL ,mmaps->st.st_size ,sam_mmap_mode(prot) ,flag ,mmaps->fd ,0);   
    if(mmaps->ptr == MAP_FAILED){
        goto err_close;
    }
    
    return sam_suc;
}
