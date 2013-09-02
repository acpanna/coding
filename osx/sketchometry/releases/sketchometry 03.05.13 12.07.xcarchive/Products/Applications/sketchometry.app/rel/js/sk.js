function Point(n,t){this.X=n;this.Y=t}function Rectangle(n,t,e,i){this.X=n;this.Y=t;this.Width=e;this.Height=i}function Template(n,t,e){this.Name=n;this.Points=Resample(e,NumPoints);var i=IndicativeAngle(this.Points);this.Points=RotateBy(this.Points,-i);this.Points=ScaleDimTo(this.Points,SquareSize,OneDThreshold);if(t)this.Points=RotateBy(this.Points,+i);this.Points=TranslateTo(this.Points,Origin);this.StartUnitVector=CalcStartUnitVector(this.Points,StartAngleIndex);this.Vector=Vectorize(this.Points,t)}function Multistroke(n,t,e){this.Name=n;this.NumStrokes=e.length;var i=new Array;for(var r=0;r<e.length;r++)i[r]=r;var o=new Array;HeapPermute(e.length,i,o);this.Templates=new Array;var a=MakeUnistrokes(e,o);for(var w=0;w<a.length;w++)this.Templates[w]=new Template(n,t,a[w])}function Result(n,t){this.Name=n;this.Score=t}var NumMultistrokes=16;var NumPoints=96;var SquareSize=250;var OneDThreshold=.25;var Origin=new Point(0,0);var Diagonal=Math.sqrt(SquareSize*SquareSize+SquareSize*SquareSize);var HalfDiagonal=.5*Diagonal;var AngleRange=Deg2Rad(45);var AnglePrecision=Deg2Rad(2);var Phi=.5*(-1+Math.sqrt(5));var StartAngleIndex=NumPoints/8;var AngleSimilarityThreshold=Deg2Rad(30);function NDollarRecognizer(n){this.Multistrokes=new Array;this.Multistrokes[0]=new Multistroke("T",n,new Array(new Array(new Point(30,7),new Point(103,7)),new Array(new Point(66,7),new Point(66,87))));this.Multistrokes[1]=new Multistroke("N",n,new Array(new Array(new Point(177,92),new Point(177,2)),new Array(new Point(182,1),new Point(246,95)),new Array(new Point(247,87),new Point(247,1))));this.Multistrokes[2]=new Multistroke("D",n,new Array(new Array(new Point(345,9),new Point(345,87)),new Array(new Point(351,8),new Point(363,8),new Point(372,9),new Point(380,11),new Point(386,14),new Point(391,17),new Point(394,22),new Point(397,28),new Point(399,34),new Point(400,42),new Point(400,50),new Point(400,56),new Point(399,61),new Point(397,66),new Point(394,70),new Point(391,74),new Point(386,78),new Point(382,81),new Point(377,83),new Point(372,85),new Point(367,87),new Point(360,87),new Point(355,88),new Point(349,87))));this.Multistrokes[3]=new Multistroke("P",n,new Array(new Array(new Point(507,8),new Point(507,87)),new Array(new Point(513,7),new Point(528,7),new Point(537,8),new Point(544,10),new Point(550,12),new Point(555,15),new Point(558,18),new Point(560,22),new Point(561,27),new Point(562,33),new Point(561,37),new Point(559,42),new Point(556,45),new Point(550,48),new Point(544,51),new Point(538,53),new Point(532,54),new Point(525,55),new Point(519,55),new Point(513,55),new Point(510,55))));this.Multistrokes[4]=new Multistroke("X",n,new Array(new Array(new Point(30,146),new Point(106,222)),new Array(new Point(30,225),new Point(106,146))));this.Multistrokes[5]=new Multistroke("H",n,new Array(new Array(new Point(188,137),new Point(188,225)),new Array(new Point(188,180),new Point(241,180)),new Array(new Point(241,137),new Point(241,225))));this.Multistrokes[6]=new Multistroke("I",n,new Array(new Array(new Point(371,149),new Point(371,221)),new Array(new Point(341,149),new Point(401,149)),new Array(new Point(341,221),new Point(401,221))));this.Multistrokes[7]=new Multistroke("exclamation",n,new Array(new Array(new Point(526,142),new Point(526,204)),new Array(new Point(526,221))));this.Multistrokes[8]=new Multistroke("line",n,new Array(new Array(new Point(12,347),new Point(119,347))));this.Multistrokes[9]=new Multistroke("five-point star",n,new Array(new Array(new Point(177,396),new Point(223,299),new Point(262,396),new Point(168,332),new Point(278,332),new Point(184,397))));this.Multistrokes[10]=new Multistroke("null",n,new Array(new Array(new Point(382,310),new Point(377,308),new Point(373,307),new Point(366,307),new Point(360,310),new Point(356,313),new Point(353,316),new Point(349,321),new Point(347,326),new Point(344,331),new Point(342,337),new Point(341,343),new Point(341,350),new Point(341,358),new Point(342,362),new Point(344,366),new Point(347,370),new Point(351,374),new Point(356,379),new Point(361,382),new Point(368,385),new Point(374,387),new Point(381,387),new Point(390,387),new Point(397,385),new Point(404,382),new Point(408,378),new Point(412,373),new Point(416,367),new Point(418,361),new Point(419,353),new Point(418,346),new Point(417,341),new Point(416,336),new Point(413,331),new Point(410,326),new Point(404,320),new Point(400,317),new Point(393,313),new Point(392,312)),new Array(new Point(418,309),new Point(337,390))));this.Multistrokes[11]=new Multistroke("arrowhead",n,new Array(new Array(new Point(506,349),new Point(574,349)),new Array(new Point(525,306),new Point(584,349),new Point(525,388))));this.Multistrokes[12]=new Multistroke("pitchfork",n,new Array(new Array(new Point(38,470),new Point(36,476),new Point(36,482),new Point(37,489),new Point(39,496),new Point(42,500),new Point(46,503),new Point(50,507),new Point(56,509),new Point(63,509),new Point(70,508),new Point(75,506),new Point(79,503),new Point(82,499),new Point(85,493),new Point(87,487),new Point(88,480),new Point(88,474),new Point(87,468)),new Array(new Point(62,464),new Point(62,571))));this.Multistrokes[13]=new Multistroke("six-point star",n,new Array(new Array(new Point(177,554),new Point(223,476),new Point(268,554),new Point(183,554)),new Array(new Point(177,490),new Point(223,568),new Point(268,490),new Point(183,490))));this.Multistrokes[14]=new Multistroke("asterisk",n,new Array(new Array(new Point(325,499),new Point(417,557)),new Array(new Point(417,499),new Point(325,557)),new Array(new Point(371,486),new Point(371,571))));this.Multistrokes[15]=new Multistroke("half-note",n,new Array(new Array(new Point(546,465),new Point(546,531)),new Array(new Point(540,530),new Point(536,529),new Point(533,528),new Point(529,529),new Point(524,530),new Point(520,532),new Point(515,535),new Point(511,539),new Point(508,545),new Point(506,548),new Point(506,554),new Point(509,558),new Point(512,561),new Point(517,564),new Point(521,564),new Point(527,563),new Point(531,560),new Point(535,557),new Point(538,553),new Point(542,548),new Point(544,544),new Point(546,540),new Point(546,536))));this.Recognize=function(n,t,e,i,r){var o=CombineStrokes(n);o=Resample(o,NumPoints);var a=IndicativeAngle(o);o=RotateBy(o,-a);o=ScaleDimTo(o,SquareSize,OneDThreshold);if(t)o=RotateBy(o,+a);o=TranslateTo(o,Origin);var w=CalcStartUnitVector(o,StartAngleIndex);var s=Vectorize(o,t);var P=+Infinity;var l=-1;for(var h=0;h<this.Multistrokes.length;h++){if(!e||n.length==this.Multistrokes[h].NumStrokes){for(var u=0;u<this.Multistrokes[h].Templates.length;u++){var v=false;for(var g=0;g<r.length;g++)if(this.Multistrokes[h].Name===r[g]){v=true;break}if(v){continue}if(AngleBetweenUnitVectors(w,this.Multistrokes[h].Templates[u].StartUnitVector)<=AngleSimilarityThreshold){var A;if(i){A=OptimalCosineDistance(this.Multistrokes[h].Templates[u].Vector,s)}else{A=DistanceAtBestAngle(o,this.Multistrokes[h].Templates[u],-AngleRange,+AngleRange,AnglePrecision)}if(A<P){P=A;l=h}}}}}return l==-1?new Result("No match.",0):new Result(this.Multistrokes[l].Name,i?1/P:1-P/HalfDiagonal)};this.AddMultistroke=function(n,t,e){this.Multistrokes[this.Multistrokes.length]=new Multistroke(n,t,e);var i=0;for(var r=0;r<this.Multistrokes.length;r++){if(this.Multistrokes[r].Name==n)i++}return i};this.DeleteUserMultistrokes=function(){this.Multistrokes.length=NumMultistrokes;return NumMultistrokes}}function HeapPermute(n,t,e){if(n==1){e[e.length]=t.slice()}else{for(var i=0;i<n;i++){HeapPermute(n-1,t,e);if(n%2==1){var r=t[0];t[0]=t[n-1];t[n-1]=r}else{var r=t[i];t[i]=t[n-1];t[n-1]=r}}}}function MakeUnistrokes(n,t){var e=new Array;for(var i=0;i<t.length;i++){for(var r=0;r<Math.pow(2,t[i].length);r++){var o=new Array;for(var a=0;a<t[i].length;a++){var w;if((r>>a&1)==1){w=n[t[i][a]].slice().reverse()}else{w=n[t[i][a]].slice()}for(var s=0;s<w.length;s++){o[o.length]=w[s]}}e[e.length]=o}}return e}function CombineStrokes(n){var t=[];for(var e=0;e<n.length;e++)for(var i=0;i<n[e].length;i++)t[t.length]=new Point(n[e][i].scrCoords[1],n[e][i].scrCoords[2]);return t}function Resample(n,t){var e=PathLength(n)/(t-1);var i=0;var r=new Array(n[0]);for(var o=1;o<n.length;o++){var a=Distance(n[o-1],n[o]);if(i+a>=e){var w=n[o-1].X+(e-i)/a*(n[o].X-n[o-1].X);var s=n[o-1].Y+(e-i)/a*(n[o].Y-n[o-1].Y);var P=new Point(w,s);r[r.length]=P;n.splice(o,0,P);i=0}else i+=a}if(r.length==t-1){r[r.length]=new Point(n[n.length-1].X,n[n.length-1].Y)}return r}function IndicativeAngle(n){var t=Centroid(n);return Math.atan2(t.Y-n[0].Y,t.X-n[0].X)}function RotateBy(n,t){var e=Centroid(n);var i=Math.cos(t);var r=Math.sin(t);var o=new Array;for(var a=0;a<n.length;a++){var w=(n[a].X-e.X)*i-(n[a].Y-e.Y)*r+e.X;var s=(n[a].X-e.X)*r+(n[a].Y-e.Y)*i+e.Y;o[o.length]=new Point(w,s)}return o}function ScaleDimTo(n,t,e){var i=BoundingBox(n);var r=Math.min(i.Width/i.Height,i.Height/i.Width)<=e;var o=new Array;for(var a=0;a<n.length;a++){var w=r?n[a].X*(t/Math.max(i.Width,i.Height)):n[a].X*(t/i.Width);var s=r?n[a].Y*(t/Math.max(i.Width,i.Height)):n[a].Y*(t/i.Height);o[o.length]=new Point(w,s)}return o}function TranslateTo(n,t){var e=Centroid(n);var i=new Array;for(var r=0;r<n.length;r++){var o=n[r].X+t.X-e.X;var a=n[r].Y+t.Y-e.Y;i[i.length]=new Point(o,a)}return i}function Vectorize(n,t){var e;var i=1;var r=0;if(t){var o=Math.atan2(n[0].Y,n[0].X);var a=Math.PI/4*Math.floor((o+Math.PI/8)/(Math.PI/4));i=Math.cos(a-o);r=Math.sin(a-o)}var w=0;var s=new Array;for(e=0;e<n.length;e++){var P=n[e].X*i-n[e].Y*r;var l=n[e].Y*i+n[e].X*r;s[s.length]=P;s[s.length]=l;w+=P*P+l*l}var h=Math.sqrt(w);for(e=0;e<s.length;e++)s[e]/=h;return s}function OptimalCosineDistance(n,t){var e=0;var i=0;for(var r=0;r<n.length;r+=2){e+=n[r]*t[r]+n[r+1]*t[r+1];i+=n[r]*t[r+1]-n[r+1]*t[r]}var o=Math.atan(i/e);return Math.acos(e*Math.cos(o)+i*Math.sin(o))}function DistanceAtBestAngle(n,t,e,i,r){var o=Phi*e+(1-Phi)*i;var a=DistanceAtAngle(n,t,o);var w=(1-Phi)*e+Phi*i;var s=DistanceAtAngle(n,t,w);while(Math.abs(i-e)>r){if(a<s){i=w;w=o;s=a;o=Phi*e+(1-Phi)*i;a=DistanceAtAngle(n,t,o)}else{e=o;o=w;a=s;w=(1-Phi)*e+Phi*i;s=DistanceAtAngle(n,t,w)}}return Math.min(a,s)}function DistanceAtAngle(n,t,e){var i=RotateBy(n,e);return PathDistance(i,t.Points)}function Centroid(n){var t=0,e=0;for(var i=0;i<n.length;i++){t+=n[i].X;e+=n[i].Y}t/=n.length;e/=n.length;return new Point(t,e)}function BoundingBox(n){var t=+Infinity,e=-Infinity,i=+Infinity,r=-Infinity;for(var o=0;o<n.length;o++){if(n[o].X<t)t=n[o].X;if(n[o].X>e)e=n[o].X;if(n[o].Y<i)i=n[o].Y;if(n[o].Y>r)r=n[o].Y}return new Rectangle(t,i,e-t,r-i)}function PathDistance(n,t){var e=0;for(var i=0;i<n.length;i++)e+=Distance(n[i],t[i]);return e/n.length}function PathLength(n){var t=0;for(var e=1;e<n.length;e++)t+=Distance(n[e-1],n[e]);return t}function Distance(n,t){var e=t.X-n.X;var i=t.Y-n.Y;return Math.sqrt(e*e+i*i)}function CalcStartUnitVector(n,t){var e=new Point(n[t].X-n[0].X,n[t].Y-n[0].Y);var i=Math.sqrt(e.X*e.X+e.Y*e.Y);return new Point(e.X/i,e.Y/i)}function AngleBetweenUnitVectors(n,t){var e=n.X*t.X+n.Y*t.Y;if(e<-1||e>+1)e=Round(e,5);return Math.acos(e)}function Round(n,t){t=Math.pow(10,t);return Math.round(n*t)/t}function Deg2Rad(n){return n*Math.PI/180}function Rad2Deg(n){return n*180/Math.PI}