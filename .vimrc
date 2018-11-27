let g:ycm_confirm_extra_conf = 0
let g:ycm_always_populate_location_list = 1

autocmd FileType cpp nnoremap <buffer><silent> <Leader>yf :YcmCompleter FixIt<CR>
autocmd FileType cpp nnoremap <buffer><silent> <C-]> :YcmCompleter GoTo<CR>
