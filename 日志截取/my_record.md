#

##
```
cat /data/yy/log/xcrs_performer_recovery/recovery.dump | grep -o ""TI"
```

##
```
zcat xcrs_control_center.log.2018-03-20.003.gz| sed -n '/16:26:00/,/16:37:59/p' >~/server.log
```

##
```
tailf xcrs_admins.log | grep "UserLevelDelete.*cost.*"

```

##

```
git log|grep ^Author|sort|uniq|sed s,^Author\:\ ,,g | awk -F " <" '{print $1 " = " $1 " <" $1 ">"}'
```