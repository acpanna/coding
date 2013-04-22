#!/bin/sh

mplayer -tv driver=v4l2:input=0:norm=pal:width=640:height=480:device=/dev/video0:alsa:adevice=hw.1,0:amode=1:audiorate=32000:immediatemode=0:chanlist=europe-west:channels=E5-ard,E6-zdf,SE5-phoenix,SE4-arte,E10-3sat,E7-swr,E12-bayern,22-wdr,SE18-ndr,SE15-hr,E11-n24,SE16-ntv,SE20-euronews,SE7-rtl,SE12-rtl2,SE14-srtl,SE8-sat1,SE11-pro7,SE13-kabel,E8-vox,SE19-mtv,23-viva,SE6-qvc,S35-hse24,S23-cnn,S22-tv5,SE9-ratv,S24-kabeldeutschland,S21-das4,SE17-9live,SE10-dsf,21-eurosport,E9-mdr:channel=zdf tv:// 

#mplayer -msglevel all=0 -ao null -vo xv -nojoystick -vf crop=632:474:4:4,pp=lb/al,hqdn3d -fs -tv driver=v4l2:amode=1:chanlist=europe-west:channels=E5-ard,E6-zdf,SE5-phoenix,SE4-arte,E10-3sat,E7-swr,E12-bayern,22-wdr,SE18-ndr,SE15-hr,E11-n24,SE16-ntv,SE20-euronews,SE7-rtl,SE12-rtl2,SE14-srtl,SE8-sat1,SE11-pro7,SE13-kabel,E8-vox,SE19-mtv,23-viva,SE6-qvc,S35-hse24,S23-cnn,S22-tv5,SE9-ratv,S24-kabeldeutschland,S21-das4,SE17-9live,SE10-dsf,21-eurosport,E9-mdr tv:// 
