/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:11:42 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/03 15:12:04 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

int main (int ac, char **av) {
    acl_t acl;
    acl_entry_t entry;
    ssize_t xattr = 0;
    char *s;

    s = ft_strnew(1);
    acl = acl_get_link_np(av[1], ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
    {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(av[1], NULL, 0, XATTR_NOFOLLOW);
    if (xattr > 0)
        s[0] = '@';
    else if (acl != NULL)
        s[0] = '+';
    else
        s[0] = ' ';

    printf("%s\n", s);
 }