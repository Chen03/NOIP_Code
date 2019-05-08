'use strict';
var http = require('http');
var lisurl = 'http://www.npc.gov.cn/delegate/dbmd.action?id=';
var iconv = require('iconv-lite'); 
var parser = new require('xml2js').Parser({explicitArray: false,strict:false});
var fs = require('fs');

// function getList(dis){
// 	http.get(lisurl+dis,function(res){;
// 		res.on('data', function (chunk) {
// 			buf=Buffer.concat([buf,chunk],buf.length+chunk.length);
// 		});
// 		res.on('end',function(){ 
// 			str = iconv.decode(buf,'GBK');
// 			fs.writeFile(dis,str,err=>console.log(err));
// 		});
// 	});
// }

class Person{
	constructor(){
		this.name="NONAME";
		this.dist="NOWHERE";
		this.sex="NOSEX";
		this.nation="NONATION";
		this.birthPlace="NOBIRTH";
		this.dateOfBirth="NOTIME";
		this.party="NOPARTY";
		this.job="NOJOB";
	}
}

var end=132987;
var i =130001;
var perurl = 'http://www.npc.gov.cn/delegate/viewDelegate.action?dbid=';
var perLis = new Array();
function getWebStr(){
	var str;
	var buf=Buffer.alloc(0);
	http.get(perurl+i,function(res){;
		res.on('data', function (chunk) {
			buf=Buffer.concat([buf,chunk],buf.length+chunk.length);
		});
		res.on('end',function(){ 
			str = iconv.decode(buf,'GBK');
			str = str.replace(/\r/g,'');
			str = str.replace(/\n/g,'');
			str = str.replace(/\t/g,'');
			str = str.slice(str.indexOf("<DIV align=center>"));
			str = str.slice(str.indexOf("<TBODY>"));
			str = str.slice(0,str.indexOf("</TABLE>"));
			// strLis.push(str);
			try{
				var per =parseStr(str);
				writeCSV(per);
				// perLis.push(per);
				console.log("Completed download "+i);
				console.log(per);
				// console.log(perLis.)
			}catch(err){
				console.log("ERROR:"+err+'\n');
				console.log(str);
				// sync2write();
				return;
			}
			if(i<end){
				setTimeout(getWebStr,10000);
				getWebStr();++i;
			}
			// else	sync2write();
		});
	});
}

// var personList = new Array();

var tes,errNum=0;
function parseStr(str){
	var xml;
	parser.parseString(str,function(err,res){
		if(err){
			console.log(err);
			++errNum;
		}
		xml = res;
	});
	if(xml===undefined){
		console.log("UNDEFINED:"+str);
	}
	tes = xml;
	xml = xml.TBODY;
	var now = new Person();
	now.name=xml.TR[0].TD[2]._;
	now.dist=xml.TR[0].TD[4]._;
	now.sex=xml.TR[1].TD[1]._;
	now.nation=xml.TR[2].TD[1]._;
	now.birthPlace=xml.TR[2].TD[3]._;
	now.dateOfBirth=xml.TR[3].TD[1]._;
	now.party=xml.TR[3].TD[3]._;
	now.job=xml.TR[4].TD[1]._;
	// personList.push()
	return now;
}

getWebStr();

// var wst = fs.createWriteStream("person.csv");
function writeCSV(tmp){
	for(var j in tmp){
		fs.writeFileSync('person.csv',tmp[j]+',',{flag:'a'});
	}
	fs.writeFileSync('person.csv','\n',{flag:'a'});
	// console.log('Safe:'+wst.writable);
	// console.log('Writing:'+wst.writableLength+' byte');
	// setTimeout(writeCSV,wst.writableLength/100);
}