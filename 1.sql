create database  mooc;
use mooc;
create table courses(cid int,cname varchar(10),ctype varchar(10), primary key (cid));
create table INSTRUCTORS(iid int,iname varchar(10),ffiliation varchar(10), primary key (iid));
create table catalog(cid int, iid int, cost real, primary key(cid,iid));
insert into courses values (1,'jk','part');
insert into courses values (2,'rek','full');
insert into courses values (3,'hed','full');
insert into courses values (4,'eat','part');
insert into courses values (5,'esrt','full');
insert into courses values (6,'gf','eeer');
select * from courses;

insert into INSTRUCTORS values (100,'fdghd df','kkt');
insert into INSTRUCTORS values (200,'lk jhkhgb','kkt');
insert into INSTRUCTORS values (300,'H.F.Korth','kkt');
insert into INSTRUCTORS values (400,'H.F.Korth','kkt');
insert into INSTRUCTORS values (50,'MB','isi k');
insert into INSTRUCTORS values (500,'hfg','isi k');

select * from INSTRUCTORS;

insert into catalog values(1,300,1000.5);
insert into catalog values(2,400,50000.5);
insert into catalog values(3,100,0);
insert into catalog values(4,200,0);
insert into catalog values(5,50,0);
insert into catalog values(6,500,1);

select * from catalog;

select cid from catalog where iid in(select iid from instructors where ffiliation='kkt')  and cost=0;

select cid from catalog where cost in (select max(cost) from catalog where iid in(select iid from instructors where iname='H.F.Korth'));

select iid from catalog where cid in( select cid from courses where ctype='part' or ctype='full');

select iid from catalog where cid in( select cid from courses where ctype='part' );