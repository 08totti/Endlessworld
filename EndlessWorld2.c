#define _CRT_SECURE_NO_WARNINGS
//forwordDungeonで使用する定義と変数
#define MAXDUNGEONFLOOR 6
//キャラクターの数
#define NUMBEROFCHARA 11
//各キャラクターに割り振られた番号
#define HERO         0
#define SLIME        1
#define PISORO	     2
#define GOLEM        3
#define DRAGON       4
#define MARTYR       5
#define PRISONER     6
#define HITMAN       7
#define HARPOON      8
#define MATUSHITA    9
#define DEVILMAN    10

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<math.h>
#include<time.h>
#include<string.h>

FILE *fp;
char file_name[] = "maou.txt";
char file_nameLEGEND[] = "LEGEND.txt";

//魔王戦のフラグ
int BMF;
//ゲーム終了分岐
int Lose;
int maouSurrender;
int maouWin;
int maouLose;

int winCount;

int herb; //薬草の所持数

//forwordDungeonで使用する定義と変数
int playerInNow;

//ゲーム説明
void GameExplanation();
//メインメニューを表示する
void MainMenu();
//物語の導入文章を表示
void FirstStory();

void printText(char*, ...);
int fight(int);

//ステータス割り振り画面
void changeStatus();

//魔王戦前のイベント
void BeforeMaouFight();

//プロトタイプ宣言
void printStory(int);
void forwordDungeon(void);

//キャラクターの情報を保存する構造体
struct CHARACTER
{
	char name[50];
	int hp;
	int str;
	int intel;
	int dex;
	int luk;
};

//キャラクターの初期化
struct CHARACTER chara[NUMBEROFCHARA] =
{
	{ "",                5,  5,  5,  3,  3 },
	{ "スライム",        3,  3,  3,  3,  3 },
	{ "魔剣士Pisoro",   10,  5,  5,  5,  5 },
	{ "ゴーレム",       13, 10,  7,  3,  7 },
	{ "ドラゴン",       13, 12, 12,  8, 10 },
	{ "司教Martyr",     20,  8, 20, 12, 12 },
	{ "脱獄囚Prisoner", 18, 20,  8, 10, 12 },
	{ "殺し屋Hitman",   15, 10, 10, 20, 15 },
	{ "天使Harpoon",    15, 10, 10, 10, 20 },
	{ "松下",           20, 18, 18, 18, 18 },
	{ "",                0,  0,  0,  0,  0 },
};

/*
//デバック用のキャラクターの情報
struct CHARACTER chara[NUMBEROFCHARA] =
{
	{ "", 5, 3, 3, 3, 3 },
	{ "スライム", 1, 1, 1, 1, 1 },
	{ "魔剣士Pisoro", 1, 1, 1, 1, 1 },
	{ "ゴーレム", 1, 1, 1, 1, 1 },
	{ "ドラゴン", 1, 1, 1, 1, 1 },
	{ "司教Martyr", 1, 1, 1, 1, 1 },
	{ "脱獄囚Prisoner", 1, 1, 1, 1, 1 },
	{ "殺し屋Hitman", 1, 1,1, 1, 1 },
	{ "天使Harpoon", 1, 1, 1, 1, 1 },
	{ "松下", 1, 1, 1, 1, 1 },
	{ "", 0, 0, 0, 0, 0 },
};
*/
//Enterで進む文章
void printText(char* str, ...)
{
	char c;
	va_list args;

	va_start(args, str);
	vprintf(str, args);
	va_end(args);

	while ((c = getchar()) != '\n');
}

void MainMenu()
{
	char c, userSelection;

	while (1)
	{
		//スクリーンをクリア
		system("cls");

		/*案1
		printf(" __, _, _ __, _,  __,  _,  _,   _  _  _, __, _,  __,\n");
		printf(" |_  |\\ | | \\ |   |_  (_  (_    |  | / \\ |_) |   | \\ \n");
		printf(" |   | \\| |_/ | , |   , ) , )   |/\\| \\ / | \\ | , |_/\n");
		printf(" ~~~ ~  ~ ~   ~~~ ~~~  ~   ~    ~  ~  ~  ~ ~ ~~~ ~   \n");
		*/


		/*案2*/
		printf("88888888888 888b      88 88888888ba,   88          88888888888 ad88888ba   ad88888ba     I8,        8        ,8I  ,ad8888ba,   88888888ba  88          88888888ba,    \n");
		printf("88          8888b     88 88      `\"8b  88          88         d8\"     \"8b d8\"     \"8b    `8b       d8b       d8' d8\"'    `\"8b  88      \"8b 88          88      `\"8b   \n");
		printf("88aaaaa     88  `8b   88 88         88 88          88aaaaa    `Y8aaaaa,   `Y8aaaaa,        Y8     8P Y8     8P  88          88 88aaaaaa8P' 88          88         88  \n");
		printf("88\"\"\"\"\"     88   `8b  88 88         88 88          88\"\"\"\"\"      `\"\"\"\"\"8b,    `\"\"\"\"\"8b,     `8b   d8' `8b   d8'  88          88 88\"\"\"\"88'   88          88         88    \n");
		printf("88          88    `8b 88 88         8P 88          88                 `8b         `8b       `8a a8'   `8a a8'   Y8,        ,8P 88    `8b   88          88         8P  \n");
		printf("88          88     `8888 88      .a8P  88          88         Y8a     a8P Y8a     a8P        `8a8'     `8a8'     Y8a.    .a8P  88     `8b  88          88      .a8P   \n");
		printf("88888888888 88      `888 88888888Y\"'   88888888888 88888888888 \"Y88888P\"   \"Y88888P\"          `8'       `8'       `\"Y8888Y\"'   88      `8b 88888888888 88888888Y\"'    \n");


		printf("\n\nエンドレスワールドへようこそ!! \n\n\n1) 説明\n2) ゲームスタート\nQ) ゲームを終わる\n");
		c = getchar();
		userSelection = c;
		while ((c = getchar()) != '\n');

		if ('1' == userSelection)
		{
			GameExplanation();
			MainMenu();
			break;
		}
		if ('2' == userSelection)
		{
			break;
		}
		if ('Q' == userSelection || 'q' == userSelection)
		{//ゲームを終わる
			exit(0);
		}
		if ('D' == userSelection || 'd' == userSelection)
		{//maou.txtファイルの削除(隠しコマンド)
			printf("よくわからないな\n");
			c = getchar();
			userSelection = c;
			if ('M' == userSelection || 'm' == userSelection)
			{
				if (0 == remove(file_name))
				{
					while ((c = getchar()) != '\n');
					printText("\n望み通りにしたよ。\n");
				}
				else
				{
					while ((c = getchar()) != '\n');
					printText("\nそれはできないようだ\n");
				}
			}

			if ('L' == userSelection || 'l' == userSelection)
			{
				if (0 == remove(file_nameLEGEND))
				{
					while ((c = getchar()) != '\n');
					printText("\n伝説は消えたよ・・・\n");
				}
				else
				{
					while ((c = getchar()) != '\n');
					printText("\nそれはできないようだ\n");
				}
			}
		}
		else
		{
			printText("よくわからないな\n");
		}
	}
}

void GameExplanation()
{
	char c;

	//スクリーンをクリア
	system("cls");

	printf("戦闘は攻撃、魔法、アイテム、回復の４つ\n"
		"攻撃はSTRの値を主に参照したダメージを、\n"
		"魔法はINTの値を主に参照したダメージを与える。\n"
		"アイテムは一定量のHPの回復、\n"
		"回復はINTを参照した量のHP回復を行う。\n"
		"これらのコマンドをターン制で敵と交互に行いHPがなくなったほうが敗北となる。\n"
		"敵を倒すと追加で割り振られるステータスポイントがもらえ、\n"
		"HP\n"
		"STR\n"
		"INT\n"
		"DEX\n"
		"LUK\n"
		"の五つに割り振ることが出来る\n");

	while ((c = getchar()) != '\n')
		;
}

void FirstStory() //富樫睦
{
	//スクリーンをクリア
	system("cls");

	printText("草原の丘の上に一軒の家が建っている。そこに%sは一人で住んでいた。", chara[HERO].name);
	printText("空は暗く淀んでいて晴れる気配はまるでない。");
	printText("%s「村人は魔王の仕業だと噂していたが・・・」", chara[HERO].name);
	printText("%sは一人窓辺に立ちつぶやく。丘の上からはふもとに広がる農地が良く見渡せた。", chara[HERO].name);
	printText("%s「もう秋だというのに稲穂はほとんど緑のままだ・・・このままでは今年の冬は厳しいな。」", chara[HERO].name);
	printText("何となく部屋の暖炉に視線を向ける。壁に立てかけてある剣が目に入った。");
	printText("鞘は磨かれていてよく手入れされていることをうかがわせる。");
	printText("しかし、%sは剣を見て顔をしかめた。この剣は昔を思い出させるのだ。", chara[HERO].name);
	printText("%sは剣を取り、住民や家畜を狼から守るために戦ったことがあった。", chara[HERO].name);
	printText("狼の群れを追い払うことに成功したが、生態系のバランスが崩れて草食動物が増殖してしまった。");
	printText("農地は荒らされ、食料は不足した。");
	printText("村人は誰も%sを責めることはなかったが、%sだけは自分自身を責め続けた。", chara[HERO].name, chara[HERO].name);
	printText("%s「もう二度と剣は取らないと誓ったのだが・・・」", chara[HERO].name);
	printText("剣を取り、鞘から抜いてみる。刀身に映った自分の顔はあの若い頃と変わらぬままだった。");
	printText("しかし、他人や自分すら信じられない疑心暗鬼な表情も変わらない。");
	printText("%s「やはり無理か・・・」", chara[HERO].name);
	printText("剣をしまうと、再び窓辺に戻る。");
	printText("%s「風が出てきたな。」・・・風が丘を吹き抜ける。", chara[HERO].name);
	printText("その風が稲穂と庭に干した洗濯物を揺らす。");
	printText("%s「この暗さでは洗濯物も乾かない・・・それは困るな。」", chara[HERO].name);
	printText("他人のためでなければ自分のために。%sは剣を取り魔王城へと向かうのであった。", chara[HERO].name);
}

//キャラクターごとのストーリーの出力
void printStory(int id)
{
	//スクリーンをクリア
	system("cls");

	switch (id)
	{
	case 1:
		//スライムのストーリー
		printText("魔王城に入るとやはりそこには魔物が居た。身体がゼリー状の・・・スライムだ。");
		printText("あまり強そうには見えないが、スライムは戦う気満々のようだ。");
		printText("%s「スライムか、肩慣らしにはちょうどよさそうだな。」", chara[HERO].name);
		printText("%sは鈍った身体を取り戻すこともかねてスライムと戦うことにした。", chara[HERO].name);
		break;
	case 2:
		//魔剣士Pisoroのストーリー
		printText("？「そこで何をしているのかな？」");
		printText("魔王城の中を特にあてもなくさまよっていると%sはいきなり声をかけられた。", chara[HERO].name);
		printText("%s「・・・お前・・・人間じゃないな？」", chara[HERO].name);
		printText("魔法を使うことができる%sは彼から放つ人間とは違う魔力を感じていた。", chara[HERO].name);
		printText("しばらくすると、人間のように見える彼はあっさりと自らの正体を明かしてくれた。");
		printText("Pisoro「ご名答。私の名前はPisoro。こう見えても魔族の端くれさ。」");
		printText("%s「俺の話は通じるみたいだな。それなら通してもらえないか?俺は魔王に話があるだけだ。」", chara[HERO].name);
		printText("「それはできない。侵入者を見つけたら必ず戦う。それがここのルールなのさ。」");
		printText("戦闘は避けられないと察した%sは剣を抜き、構えた。", chara[HERO].name);
		break;
	case 3:
		//ゴーレムのストーリー
		printText("魔王城の探索を続ける%sは大きな広間にたどり着いた。", chara[HERO].name);
		printText("広間には巨大な石柱や石像などが設置されており、広いが圧迫感を感じた。");
		printText("%s「あの石像だけやけに大きいな・・・」", chara[HERO].name);
		printText("確かにその石像は他の石像よりも一回り大きい。それに奇妙なオーラを感じる。");
		printText("%sいやな予感がしたので距離を置いて観察することにした。", chara[HERO].name);
		printText("%s「なるほど・・・そうか。」", chara[HERO].name);
		printText("よく観察してみると、巨大な石像の胸部に魔法陣が書かれていた。");
		printText("%s「あれはおそらくゴーレムだな。魔法生物はやっかいだ・・・」", chara[HERO].name);
		printText("その時、一向に近づいてこないのにしびれを切らしたのか、ゴーレムが動き出した。");
		printText("%s「これは避けて進むのは無理そうだな。」", chara[HERO].name);
		printText("%sはゴーレムとの戦いに挑むのであった。", chara[HERO].name);
		break;
	case 4:
		//ドラゴンのストーリー
		printText("さらに進むと天井が開けた筒状の塔のような広場に出た。");
		printText("見上げると真っ青な空で太陽の光がまぶしく差し込んでいる。");
		printText("視線をまっすぐに戻すと、硬そうな鱗で覆われた巨大生物が尾を丸めて寝ていた。");
		printText("%s「ドラゴン・・・」", chara[HERO].name);
		printText("幸いにも、寝ていたので静かに通り抜けようとした。");
		printText("しかし、ドラゴンは鼻が良い。100メートル先の獣の臭いを察知できるらしい。");
		printText("度重なる戦いで%sは傷ついていた。", chara[HERO].name);
		printText("ドラゴンは寝ていたが目の前でわずかに流れ出ている血の臭いを逃さなかった。");
		printText("大きな目を見開くと真っすぐとこちらを睨んだ。");
		printText("%s「やはり気づかれてしまったか・・・」", chara[HERO].name);
		printText("ドラゴンは立ち上がると翼を広げ、唸るような雄たけびを上げる。");
		printText("その翼を羽ばたかせると砂埃が舞うほど凄まじく、%sは思わず顔を腕で覆った。", chara[HERO].name);
		printText("「これは厳しい戦いになりそうだ。」");
		printText("%sは持っている剣を、より強く握りしめた。", chara[HERO].name);
		break;
	case 5:
		//司教Martyrのストーリー(INT強化)
		printText("%sは城のだいぶ上層階へ来ていた。覗き穴から上を見るとこれより上の階はほぼ無い。", chara[HERO].name);
		printText("頂上まであと少し、魔王と遭うのも近いと思った。");
		printText("？「見かけない姿ですが、こんなところに何用で？」");
		printText("不意に背後から声をかけられたので、%sは後ずさりしつつ剣を構える。", chara[HERO].name);
		printText("？「私は怪しい者ではありません。ここで司教を務めております。」");
		printText("Martyr「名前はMartyrと申します。」");
		printText("%s「その名前・・・それに本や杖も怪しい！」", chara[HERO].name);
		printText("Martyr「どなたか存じ上げませんが、ここにいては危ない。」");
		printText("Martyr「大人しく帰られることをお勧めします。」");
		printText("%s「そうはいかない、俺は魔王に用があるのでね。」", chara[HERO].name);
		printText("Martyr「あなた、さては%sさん・・・魔王と会ってはいけない。」", chara[HERO].name);
		printText("Martyr「取り返しのつかないことになりますよ。」");
		printText("%s「俺はただ魔王と話がしたいだけなんだ。通してくれ！」", chara[HERO].name);
		printText("%sは剣先を真っすぐ司教Martyrの方へ向けた。", chara[HERO].name);
		printText("Martyr「私はあなたのような冒険者をこれまで何人も見てきた。しかし戻って来た者はいません。」");
		printText("Martyr「これ以上犠牲を増やすわけにはいかないのです。意地でも行かせませんよ。」");
		printText("どうやらただでは通してくれないようだ。%sはボロボロな身体を奮い立たせ、走り出した。", chara[HERO].name);
		break;
	case 6:
		//脱獄囚Prisonerのストーリー(STR強化)
		printText("%sは城のだいぶ上層階へ来ていた。覗き穴から上を見るとこれより上の階はほぼ無い。", chara[HERO].name);
		printText("頂上まであと少し、魔王と遭うのも近いと思った。");
		printText("？「あら～こんなところにいい男いるじゃな～い」");
		printText("不意に背後から気味の悪い甲高い男の声がしたので、%sは自分でも驚くほどの速度で後ずさりしつつ剣を構える。", chara[HERO].name);
		printText("？「やっぱいい男～！わたしの目は狂ってなかったわ～！」");
		printText("一人で興奮しながら、腕で自分の胸を抱いている。ますます気味が悪い。");
		printText("%s「おまえは誰だ！」", chara[HERO].name);
		printText("Prisoner「わたしはいつも牢獄に入れられてるからPrisonerと呼ばれてるわ！あなたは？」");
		printText("%s「俺の名前はどうでもいい、それよりここを通してくれるか。」", chara[HERO].name);
		printText("Prisoner「いや～ん、サディスティックなイケメン最高～」");
		printText("かなりイライラする奴だ。いっそのこと殺してしまいたいくらいだ。");
		printText("しかし近くでよく見るとその身体の巨大さ、筋肉のつき方は異常である。");
		printText("%s「お前は普段牢獄に閉じ込められてるのではないのか。」", chara[HERO].name);
		printText("Prisoner「退屈だから、また檻を壊して抜け出してきちゃった。」");
		printText("Prisoner「新しい囚人が収容されてないか見回ってただけよ。」");
		printText("城の上を目指す途中、所々に牢獄はいくつもあった。しかし人の姿は無く、どの檻も壊れていた。");
		printText("%s「まさか・・・お前が全部の檻を！」", chara[HERO].name);
		printText("Prisoner「ここに来た囚人どもは、み～んな食べちゃったんだから！」");
		printText("Prisoner「それにしても、今晩のおかず・・・特上品ね！！！」");
		printText("Prisonerは少しずつ%sに近づいてくる。思わず後ずさりしたが、先に進まなければいけない。", chara[HERO].name);
		printText("%sはボロボロな身体を奮い立たせ、前に走り出した。", chara[HERO].name);
		break;
	case 7:
		//殺し屋Hitmanのストーリー(DEX強化)
		printText("%sは城のだいぶ上層階へ来ていた。覗き穴から上を見るとこれより上の階はほぼ無い。", chara[HERO].name);
		printText("頂上まであと少し、魔王と遭うのも近いと思った。");
		printText("後ろからとてつもない殺気を感じ、%sは思わず振り返り、後ずさりしつつ剣を構える。", chara[HERO].name);
		printText("%sの後ろにはいつの間にか男が立っていた。", chara[HERO].name);
		printText("%s「お前は誰だ。」", chara[HERO].name);
		printText("Hitman「俺か？俺の名はHitmanだ。元軍人だが、魔王に雇われて殺し屋をやっている。」");
		printText("見た目はそこらにいそうな猟師だが、放つオーラは禍々しい。");
		printText("銃やら武器を隠し持っていそうで、瞬きしている間に殺されそうな気迫だ。");
		printText("Hitman「お前は誰か、どうやって入ってきたか知らないが、いい子なら早く帰った方がいいぜ。」");
		printText("%s「俺は魔王に用がある、通してほしい。」", chara[HERO].name);
		printText("Hitman「そうはいかねえなあ、俺は魔王のボディガードも務めてるんでね。」");
		printText("Hitman「お前、いいオーラ出してるな。今までどれほどの数の命を奪ってきた？」");
		printText("Hitmanの殺気がより強くなった。あまりのオーラに自分の身体がのけぞりそうになっている。");
		printText("Hitman「まあいいや、丁度いい。俺の的になれ。」");
		printText("ふと気が付くと既に彼の手には拳銃が握られており、こちらに向けられていた。");
		printText("バンッ！");
		printText("狭い通路でギリギリ体制を低くし、かわした。");
		printText("あと0.1秒遅かったら撃たれてたかもしれない。次は当てられてもおかしくない。");
		printText("Hitman「いい動きだ！やはり俺が見込んだ通りだ！」");
		printText("もう戦うしかない。%sはボロボロな身体を奮い立たせ、低い姿勢のまま真っすぐに走り出した。", chara[HERO].name);
		break;
	case 8:
		//天使Harpoonのストーリー(LUK強化)
		printText("%sは城のだいぶ上層階へ来ていた。覗き穴から上を見るとこれより上の階はほぼ無い。", chara[HERO].name);
		printText("頂上まであと少し、魔王と遭うのも近いと思った。");
		printText("？「・・・誰？」");
		printText("不意に背後から女の子の高い声がして、%sは振り返り思わず剣を構える。", chara[HERO].name);
		printText("白いワンピースを着た、金色の膝辺りまで伸びる長い髪の女の子。");
		printText("片手には先端が銛の形をした槍を持っている。");
		printText("そして、背中にはその子の身長の倍はある翼が生えており、狭い通路を遮っていた。");
		printText("%s「・・・天使？」", chara[HERO].name);
		printText("？「あなたは天使ではないでしょう。」");
		printText("Harpoon「私の名前はHarpoon。魔王様に救われてこの城を守っています。」");
		printText("%s「俺は魔王に用がある、通してほしい。」", chara[HERO].name);
		printText("Harpoon「そうはいきません、あなたが魔王様の元へ向かったところでどうなるのですか？」");
		printText("%s「天が暗くて洗濯物が乾かないから、晴らせてもらいにきたんだ。」", chara[HERO].name);
		printText("Harpoon「フフフッ・・・馬鹿な冗談は止してください。」");
		printText("Harpoon「魔王様はある計画を遂行しようとしているのです。あなたに邪魔をさせない！」");
		printText("天使は翼を大きく数回羽ばたかせると、足が地を離れたと同時に真っすぐこちらへ飛んできた。");
		printText("Harpoon「魔王様に代わってあなたに裁きを下します！」");
		printText("逃げる暇もない、どうやら戦うしかないようだ。");
		printText("%sは剣を振り上げ、迫りくる天使や運命に抗おうとするのだった。", chara[HERO].name);
		break;
	case 9:
		//松下のストーリー
		printText("とうとう最上階までやって来た。大きな鉄の扉がその奥にいる魔王の存在を示している。");
		printText("鈍い音を立てて扉が開く。魔王は一体どんな奴なのだろうか。");
		printText("中に入ると思いのほか広くはなく、周囲には見たことのない機械などが並んでいる。");
		printText("？「よくぞ来た。」");
		printText("奥から男の声がしたので、近づいてみる。");
		printText("部屋の奥のオフィスデスクに眼鏡をかけた黒いワイシャツの男がいた。");
		printText("%s「お前が魔王か？」", chara[HERO].name);
		printText("松下「そうだ、わたしが魔王、松下だ。」");
		printText("松下「これは面白い。ここに来るまでに私の部下が大量にいたはずだが。」");
		printText("%s「途中に出てきたやつらは全部倒してきたぜ。」", chara[HERO].name);
		printText("松下「実に素晴らしい！身体をそこまでボロボロにして君は何をしに来たのかね。");
		printText("%s「空が暗すぎて自宅の洗濯物が乾かない、晴れさせてくれ。」", chara[HERO].name);
		printText("松下「・・・それを言うために、わざわざここまで来たのですか？」");
		printText("%s「そうだ、困るんだ。」", chara[HERO].name);
		printText("松下「わたしはある実験をしている。」");
		printText("松下「結果を論文にまとめるまで、その願いは聞けないのだ。」");
		printText("%s「なら力尽くで止める！」", chara[HERO].name);
		printText("%sは剣を抜き、松下に向かって真っすぐ走り出した。", chara[HERO].name);
		printText("突如、足の裏に刺すような痛みを感じ、地面に転がり込んだ。");
		printText("%s「なんだ、トラップか!?」", chara[HERO].name);
		printText("床には小さく黒い塊からトゲが生えたものが無数に転がっていた。");
		printText("松下「おや、どうやらICチップが床に散乱していたようだ。」");
		printText("襲われようとしていたにも関わらず、動く様子もなく機械と向き合っていた。");
		printText("松下「ところで君はまだ若いようだが、勉学はしているのかね?」");
		printText("言葉が心に刺さる。%sは勉学をしたくなかったため、小さい時から農業に勤しんでいた。", chara[HERO].name);
		printText("学校や勉学とは無縁な関係な人生を送るつもりだった。");
		printText("松下「私は魔王と呼ばれているが、子供たちのために学校を開いている。」");
		printText("松下「勉学に励み、学校を卒業できたら街の方の役所に優先的に入れるのだ。」");
		printText("役所と言えば農民の%sから見たら高給で、エリートしか入れない花形職業だ。", chara[HERO].name);
		printText("そのようなものには釣られないと言うつもりだったが、%sは金欠の身、心が動かされる。", chara[HERO].name);
		printText("松下「わたしは待っていた。君のような強く優秀な若者が現れることを。」");
		break;
	case 10:
		//NewBossのストーリー
		printText("とうとう最上階までやって来た。大きな鉄の扉がその奥にいる魔王の存在を示している。");
		printText("鈍い音を立てて扉が開く。魔王は一体どんな奴なのだろうか。");
		printText("やや広い部屋には机や機械、部品などが散乱している。");
		printText("魔王の部屋としては予想に反してかなり汚い、まるで荒らされたようだ。");
		printText("奥に進むと黒いマントにフードを被る男が窓から外を眺めていた。");
		printText("%s「お前が魔王か？」", chara[HERO].name);
		printText("男はこちらをゆっくりと振り向いた、フードで顔はまだ見えない。");
		printText("？「おお、久々に冒険者を見たな。」");
		printText("%sは剣を抜き、剣先を魔王に向ける。", chara[HERO].name);
		printText("？「魔王？ああ、あいつならとうの前に倒したよ。」");
		printText("%s「ならお前は一体誰だ。お前はここで何をしている。」", chara[HERO].name);
		printText("？「昔の俺にそっくりだな。まるで自分と対峙している気分だ。」");
		printText("魔王はフードを脱いだ。その途端、%sは動揺のあまり、剣を落としてしまった。", chara[HERO].name);
		printText("%s「あなたは・・・村のために戦った・・・%sさん！！」", chara[HERO].name, chara[DEVILMAN].name);
		printText("%s「まだ俺の名前を知っている奴がいたのか。」", chara[DEVILMAN].name);
		printText("%s「あなたが村でしたことは正しかったはずだ。なのに村の人たちは冷ややかな目で見ていた。」", chara[HERO].name);
		printText("%s「だけど俺は、あなたみたいに誰もやりたがらないことを進んでやれる人はかっこよかったと思う！」", chara[HERO].name);
		printText("%s「魔王を倒したなら、なぜ村に戻ってきてくれないのですか？」", chara[HERO].name);
		printText("%s「昔、俺は魔王を倒して、村に帰ったら英雄になれると思っていた。」", chara[DEVILMAN].name);
		printText("%s「だがな、もう村にも未練はない。」", chara[DEVILMAN].name);
		printText("%s「なぜです！」", chara[HERO].name);
		printText("%s「アダムとイヴの神話を知っているか？」", chara[DEVILMAN].name);
		printText("%s「禁断の果実を手にした彼らは無垢を忘れ、知恵を得てしまう。」", chara[DEVILMAN].name);
		printText("%s「俺は故郷の村を捨て、魔王を倒し、力を得た。」", chara[DEVILMAN].name);
		printText("%s「そして今、この力を試せる者が目の前にいる！！」", chara[DEVILMAN].name);
		printText("%s「俺はあなたと戦いたくない。村に帰りましょう！」", chara[HERO].name);
		printText("%s「もし戦わなければ村に災いがもたらされるだろう。」", chara[DEVILMAN].name);
		printText("%sが手を振り上げた瞬間、窓に眩い光が差し込むと同時に爆発したような轟音が天に響き渡った。", chara[DEVILMAN].name);
		printText("%s「・・・雷？」", chara[HERO].name);
		printText("%s「次は村に降り注ぐぞ。」", chara[DEVILMAN].name);
		printText("%sはかつての英雄と戦わなくてはならないようだ。", chara[HERO].name);
		break;
	default:
		break;
	}
}

//ダンジョンを進む関数(呼び出す度に進む)
void forwordDungeon(void)
{
	char c;
	char space[] = { "                                     " };
	int i;
	playerInNow++;

	//スクリーンをクリア
	system("cls");

	for (i = MAXDUNGEONFLOOR; i >= 1; i--)
	{
		if (i == MAXDUNGEONFLOOR)
		{
			printf("%s+---+\n", space);
		}
		else
		{
			printf("%s+- -+\n", space);
		}
		printf("%s| %d |", space, i);

		if (i == playerInNow)
		{
			printf(" ←\n");
		}
		else
		{
			printf("\n");
		}

		if (i == 1)
		{
			printf("%s+---+\n", space);
		}
		else
		{
			printf("%s+- -+\n%s | | \n", space, space);
		}
	}

	for (i = 0; i < 3; i++)
	{
		printf("\n");
	}

	while ((c = getchar()) != '\n');

	//スクリーンをクリア
	system("cls");
}

//ステータス割り振り
void changeStatus()
{
	char c, userSelection;
	char string[10];
	int i, upOrDown;
	int ap = 10;

	int hpUp = 0;
	int strUp = 0;
	int intelUp = 0;
	int dexUp = 0;
	int lukUp = 0;

	while (1)
	{
		//スクリーンをクリア
		system("cls");

		printf("ステータス割り振り\n");
		printf("HP :%d + %d ⇒ %d\n", chara[HERO].hp, hpUp, chara[HERO].hp + hpUp);
		printf("STR:%d + %d ⇒ %d\n", chara[HERO].str, strUp, chara[HERO].str + strUp);
		printf("INT:%d + %d ⇒ %d\n", chara[HERO].intel, intelUp, chara[HERO].intel + intelUp);
		printf("DEX:%d + %d ⇒ %d\n", chara[HERO].dex, dexUp, chara[HERO].dex + dexUp);
		printf("LUK:%d + %d ⇒ %d\n", chara[HERO].luk, lukUp, chara[HERO].luk + lukUp);

		if (ap == 0)
		{
			while (1)
			{
				printf("\nこちらでよろしいですか?\n");
				printf("1)はい\n");
				printf("2)いいえ\n");

				c = getchar();
				userSelection = c;
				while ((c = getchar()) != '\n')
					;
				if ('1' == userSelection || '2' == userSelection) { break; }
				else
				{
					printText("隠しコマンドとか無いよ?");
					system("cls");

					printf("ステータス割り振り\n");
					printf("HP :%d + %d ⇒ %d\n", chara[HERO].hp, hpUp, chara[HERO].hp + hpUp);
					printf("STR:%d + %d ⇒ %d\n", chara[HERO].str, strUp, chara[HERO].str + strUp);
					printf("INT:%d + %d ⇒ %d\n", chara[HERO].intel, intelUp, chara[HERO].intel + intelUp);
					printf("DEX:%d + %d ⇒ %d\n", chara[HERO].dex, dexUp, chara[HERO].dex + dexUp);
					printf("LUK:%d + %d ⇒ %d\n", chara[HERO].luk, lukUp, chara[HERO].luk + lukUp);
				}
			}

			if (userSelection == '1')
			{
				chara[HERO].hp = chara[HERO].hp + hpUp;
				chara[HERO].str = chara[HERO].str + strUp;
				chara[HERO].intel = chara[HERO].intel + intelUp;
				chara[HERO].dex = chara[HERO].dex + dexUp;
				chara[HERO].luk = chara[HERO].luk + lukUp;
				break;
			}
		}

		printf("\n変更したいステータスを教えてください	所持AP : %d\n", ap);
		printf("1)HP\n");
		printf("2)STR\n");
		printf("3)INT\n");
		printf("4)DEX\n");
		printf("5)LUK\n");

		c = getchar();
		userSelection = c;
		while ((c = getchar()) != '\n')
			;

		switch (userSelection)
		{
		case '1':
			//hpの変更
			if (ap == 0)
			{
				while (1)
				{
					printf("どれだけ下げますか? HPの上昇量 : %d\n", hpUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);
					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= hpUp)
					{
						hpUp = hpUp - i;
						ap = ap + i;
						break;
					}
					else if (0 > hpUp - i)
					{
						printf("一度確定したものを変えることはできない・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			else if (hpUp != 0)
			{
				while (1)
				{
					printf("+しますか?それとも-しますか?\n");
					printf("1)+\n");
					printf("2)-\n");

					c = getchar();
					userSelection = c;
					while ((c = getchar()) != '\n');

					if (userSelection == '1')
					{
						upOrDown = 1;
						break;
					}
					else if (userSelection == '2')
					{
						upOrDown = (-1);
						break;
					}
					else
					{
						printf("\n人生は二択の連続だ\n");
						while ((c = getchar()) != '\n');
					}
				}

				while (1)
				{
					printf("\nどれだけ変更しますか? 所持AP : %d   HPの上昇量 : %d\n", ap, hpUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (upOrDown == 1)
					{
						if (i <= ap)
						{
							hpUp = hpUp + (i * upOrDown);
							ap = ap - i;
							break;
						}
						else if (i > ap)
						{
							printf("そんなに成長できないようだ・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
					else
					{
						if (i <= hpUp)
						{
							hpUp = hpUp + (i * upOrDown);
							ap = ap + i;
							break;
						}
						else if (0 > hpUp - i)
						{
							printf("一度確定したものを変えることはできない・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
				}
			}
			else
			{
				while (1)
				{
					printf("\nどれだけ上げますか? 所持AP : %d\n", ap);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= ap)
					{
						hpUp = hpUp + i;
						ap = ap - i;
						break;
					}
					else if (i > ap)
					{
						printf("そんなに成長できないようだ・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			break;

		case '2':
			//strの変更
			if (ap == 0)
			{
				while (1)
				{
					printf("どれだけ下げますか? STRの上昇量 : %d\n", strUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= strUp)
					{
						strUp = strUp - i;
						ap = ap + i;
						break;
					}
					else if (0 > strUp - i)
					{
						printf("一度確定したものを変えることはできない・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			else if (strUp != 0)
			{
				while (1)
				{
					printf("+しますか?それとも-しますか?\n");
					printf("1)+\n");
					printf("2)-\n");

					c = getchar();
					userSelection = c;
					while ((c = getchar()) != '\n');

					if (userSelection == '1')
					{
						upOrDown = 1;
						break;
					}
					else if (userSelection == '2')
					{
						upOrDown = (-1);
						break;
					}
					else
					{
						printf("\n人生は二択の連続だ\n");
						while ((c = getchar()) != '\n');
					}
				}

				while (1)
				{
					printf("\nどれだけ変更しますか? 所持AP : %d   STRの上昇量 : %d\n", ap, strUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (upOrDown == 1)
					{
						if (i <= ap)
						{
							strUp = strUp + (i * upOrDown);
							ap = ap - i;
							break;
						}
						else if (i > ap)
						{
							printf("そんなに成長できないようだ・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
					else
					{
						if (i <= strUp)
						{
							strUp = strUp + (i * upOrDown);
							ap = ap + i;
							break;
						}
						else if (0 > strUp - i)
						{
							printf("一度確定したものを変えることはできない・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
				}
			}
			else
			{
				while (1)
				{
					printf("\nどれだけ上げますか? 所持AP : %d\n", ap);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= ap)
					{
						strUp = strUp + i;
						ap = ap - i;
						break;
					}
					else if (i > ap)
					{
						printf("そんなに成長できないようだ・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			break;

		case '3':
			//intの変更
			if (ap == 0)
			{
				while (1)
				{
					printf("どれだけ下げますか? INTの上昇量 : %d\n", intelUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= intelUp)
					{
						intelUp = intelUp - i;
						ap = ap + i;
						break;
					}
					else if (0 > intelUp - i)
					{
						printf("一度確定したものを変えることはできない・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			else if (intelUp != 0)
			{
				while (1)
				{
					printf("+しますか?それとも-しますか?\n");
					printf("1)+\n");
					printf("2)-\n");

					c = getchar();
					userSelection = c;
					while ((c = getchar()) != '\n');

					if (userSelection == '1')
					{
						upOrDown = 1;
						break;
					}
					else if (userSelection == '2')
					{
						upOrDown = (-1);
						break;
					}
					else
					{
						printf("\n人生は二択の連続だ\n");
						while ((c = getchar()) != '\n');
					}
				}

				while (1)
				{
					printf("\nどれだけ変更しますか? 所持AP : %d   INTの上昇量 : %d\n", ap, intelUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (upOrDown == 1)
					{
						if (i <= ap)
						{
							intelUp = intelUp + (i * upOrDown);
							ap = ap - i;
							break;
						}
						else if (i > ap)
						{
							printf("そんなに成長できないようだ・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
					else
					{
						if (i <= intelUp)
						{
							intelUp = intelUp + (i * upOrDown);
							ap = ap + i;
							break;
						}
						else if (0 > intelUp - i)
						{
							printf("一度確定したものを変えることはできない・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
				}
			}
			else
			{
				while (1)
				{
					printf("\nどれだけ上げますか? 所持AP : %d\n", ap);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= ap)
					{
						intelUp = intelUp + i;
						ap = ap - i;
						break;
					}
					else if (i > ap)
					{
						printf("そんなに成長できないようだ・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			break;

		case '4':
			//dexの変更
			if (ap == 0)
			{
				while (1)
				{
					printf("どれだけ下げますか? DEXの上昇量 : %d\n", dexUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= dexUp)
					{
						dexUp = dexUp - i;
						ap = ap + i;
						break;
					}
					else if (0 > dexUp - i)
					{
						printf("一度確定したものを変えることはできない・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			else if (dexUp != 0)
			{
				while (1)
				{
					printf("+しますか?それとも-しますか?\n");
					printf("1)+\n");
					printf("2)-\n");

					c = getchar();
					userSelection = c;
					while ((c = getchar()) != '\n');

					if (userSelection == '1')
					{
						upOrDown = 1;
						break;
					}
					else if (userSelection == '2')
					{
						upOrDown = (-1);
						break;
					}
					else
					{
						printf("\n人生は二択の連続だ\n");
						while ((c = getchar()) != '\n');
					}
				}

				while (1)
				{
					printf("\nどれだけ変更しますか? 所持AP : %d   DEXの上昇量 : %d\n", ap, dexUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (upOrDown == 1)
					{
						if (i <= ap)
						{
							dexUp = dexUp + (i * upOrDown);
							ap = ap - i;
							break;
						}
						else
						{
							printf("そんなに成長できないようだ・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
					else
					{
						if (i <= dexUp)
						{
							dexUp = dexUp + (i * upOrDown);
							ap = ap + i;
							break;
						}
						else if (0 > dexUp - i)
						{
							printf("一度確定したものを変えることはできない・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
				}
			}
			else
			{
				while (1)
				{
					printf("\nどれだけ上げますか? 所持AP : %d\n", ap);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= ap)
					{
						dexUp = dexUp + i;
						ap = ap - i;
						break;
					}
					else if (i > ap)
					{
						printf("そんなに成長できないようだ・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			break;

		case '5':
			//lukの変更
			if (ap == 0)
			{
				while (1)
				{
					printf("どれだけ下げますか? LUKの上昇量 : %d\n", lukUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= lukUp)
					{
						dexUp = dexUp - i;
						ap = ap + i;
						break;
					}
					else if (0 > lukUp - i)
					{
						printf("一度確定したものを変えることはできない・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			else if (lukUp != 0)
			{
				while (1)
				{
					printf("+しますか?それとも-しますか?\n");
					printf("1)+\n");
					printf("2)-\n");

					c = getchar();
					userSelection = c;
					while ((c = getchar()) != '\n');

					if (userSelection == '1')
					{
						upOrDown = 1;
						break;
					}
					else if (userSelection == '2')
					{
						upOrDown = (-1);
						break;
					}
					else
					{
						printf("\n人生は二択の連続だ\n");
						while ((c = getchar()) != '\n');
					}
				}

				while (1)
				{
					printf("\nどれだけ変更しますか? 所持AP : %d   LUKの上昇量 : %d\n", ap, lukUp);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (upOrDown == 1)
					{
						if (i <= ap)
						{
							lukUp = lukUp + (i * upOrDown);
							ap = ap - i;
							break;
						}
						else if (i > ap)
						{
							printf("そんなに成長できないようだ・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
					else
					{
						if (i <= lukUp)
						{
							lukUp = lukUp + (i * upOrDown);
							ap = ap + i;
							break;
						}
						else if (0 > lukUp - i)
						{
							printf("一度確定したものを変えることはできない・・・\n");
							while ((c = getchar()) != '\n');
						}
					}
				}
			}
			else
			{
				while (1)
				{
					printf("\nどれだけ上げますか? 所持AP : %d\n", ap);

					fgets(string, sizeof(string), stdin);
					string[strlen(string) - 1] = '\0';

					i = atoi(string);

					if (i < 0)
					{
						printf("+の値を入力してください\n");
						while ((c = getchar()) != '\n');
					}
					else if (i <= ap)
					{
						lukUp = lukUp + i;
						ap = ap - i;
						break;
					}
					else if (i > ap)
					{
						printf("そんなに成長できないようだ・・・\n");
						while ((c = getchar()) != '\n');
					}
				}
			}
			break;

		default:
			printf("そんな能力・・・うちにはないよ・・・\n");
			break;
		}
	}
}

//戦闘
int fight(int enemyId)
{
	char c, userSelection;
	int a, i;
	double rnd, damage;

	//乱数シードの設定
	srand((unsigned)time(NULL));

	//戦闘で使うプレイヤーの変数宣言
	double heroHp, heroHpBuf, heroAttack, heroMagic, heroHeal, heroHit, heroAtkWidth;
	//戦闘で使う敵の変数宣言
	double enemyHp, enemyHpBuf, enemyAttack, enemyMagic, enemyHeal, enemyHit, enemyAtkWidth;


	//変数の初期化
	heroHp = chara[HERO].hp * 10.0;
	heroHpBuf = heroHp;
	heroAttack = floor((pow(chara[HERO].str, 10) - chara[enemyId].str) / (pow(chara[HERO].str, 9) + chara[enemyId].str) * (chara[HERO].str - chara[enemyId].str + 20) / 10);
	heroMagic = floor((pow(chara[HERO].intel, 10) - chara[enemyId].intel) / (pow(chara[HERO].intel, 9) + chara[enemyId].intel) * (chara[HERO].intel - chara[enemyId].intel + 15) / 10);
	heroHeal = floor((chara[HERO].intel * 2) + (chara[HERO].luk * 1.5));
	heroHit = 0.2 + (pow(chara[HERO].luk, 1.1) / pow(chara[enemyId].luk, 1.5));
	heroAtkWidth = pow(((chara[HERO].dex * 1.75) + (chara[HERO].str * 0.25)) / 2, 1.1);

	enemyHp = chara[enemyId].hp * 10.0;
	enemyHpBuf = enemyHp;
	enemyAttack = floor((pow(chara[enemyId].str, 10) - chara[HERO].str) / (pow(chara[enemyId].str, 9) + chara[HERO].str) * (chara[enemyId].str - chara[HERO].str + 20) / 10);
	enemyMagic = floor((pow(chara[enemyId].intel, 10) - chara[HERO].intel) / (pow(chara[enemyId].intel, 9) + chara[HERO].intel) * (chara[enemyId].intel - chara[HERO].intel + 15) / 10);
	enemyHeal = floor((chara[enemyId].intel * 2) + (chara[enemyId].luk * 1.2));
	enemyHit = 0.2 + (pow(chara[enemyId].luk, 1.1) / pow(chara[HERO].luk, 1.5));
	enemyAtkWidth = pow(((chara[enemyId].dex * 1.75) + (chara[enemyId].str * 0.25)) / 2, 1.1);

	//デバッグ用表示
	//printf("hero : %d,%d,%d,%f,%d\n", (int)heroAttack, (int)heroMagic, (int)heroHeal, heroHit, (int)heroAtkWidth);
	//printf("enemy : %d,%d,%d,%f,%d\n", (int)enemyAttack, (int)enemyMagic, (int)enemyHeal, enemyHit, (int)enemyAtkWidth);

	i = 1;

	//初期状態の表示
	//printText("\n%sがあらわれた!\n", chara[enemyId].name);
	//printf("%s HP:%d\n\n", chara[HERO].name, (int)heroHp);

	while (1)
	{
		while (1)
		{
			//乱数調節
			rand(); rand(); rand(); rand(); rand();
			//スクリーンをクリア
			system("cls");

			printf("第%dターン\n\n", i);
			//主人公のターン
			printf("あなたの番です\n\n");

			if (1 == maouSurrender)
			{
				printf("\n%sには戦う気力が残っていない!\n\n", chara[HERO].name);
				break;
			}
			else
			{
				printf("%s HP %d/%d\n\n", chara[HERO].name, (int)heroHp, (int)heroHpBuf);
				printf("どうする?\n");
				printf("1)攻撃\n");
				printf("2)魔法\n");
				printf("3)回復\n");
				printf("4)薬草 : 残り%d個\n\n", herb);

				c = getchar();
				userSelection = c;
				while ((c = getchar()) != '\n');

				if (userSelection == '1')
				{
					//物理攻撃

					printf("%sの攻撃!\n", chara[HERO].name);
					//攻撃成功判定
					int hit;
					
					rnd = rand() % 101;
					//デバッグ用表示
					//printf("%f\n", rnd);

					//ヒット判定
					if (heroHit > rnd / 100)
					{
						hit = 1;
					}
					else
					{
						hit = 0;
					}

					//ダメージ計算
					if (heroAttack < heroAtkWidth)
					{
						damage = heroAtkWidth;
					}
					else
					{
						damage = rand() % ((int)heroAttack - (int)heroAtkWidth) + heroAtkWidth;
					}

					//攻撃結果
					if (hit == 1 && damage > 0)
					{
						printf("%sに%dのダメージ!\n", chara[enemyId].name, (int)damage);
					}
					else if(hit == 1 && damage <= 0)
					{
						damage = 1;
						printf("%sに%dのダメージ!\n", chara[enemyId].name, (int)damage);
					}
					else // hit = 0
					{
						damage = 0;
						printf("ミス!%sの攻撃は外れてしまった!\n", chara[HERO].name);
					}

					enemyHp -= damage;

					while ((c = getchar()) != '\n')
						;

					break;
				}
				else if (userSelection == '2')
				{
					//魔法

					printf("%sの魔法攻撃!\n", chara[HERO].name);
					//攻撃成功判定
					int hit;
					rnd = rand() % 101;
					//デバッグ用表示
					//printf("%f\n", rnd);

					//ヒット判定
					if (heroHit > rnd / 100)
					{
						hit = 1;
					}
					else
					{
						hit = 0;
					}

					//ダメージ計算
					if (heroMagic < heroAtkWidth)
					{
						damage = heroAtkWidth;
					}
					else
					{
						damage = rand() % ((int)heroMagic - (int)heroAtkWidth) + heroAtkWidth;
					}

					//攻撃結果
					if (hit == 1 && damage > 0)
					{
						printf("%sに%dのダメージ!\n", chara[enemyId].name, (int)damage);
					}
					else if (hit == 1 && damage <= 0)
					{
						damage = 1;
						printf("%sに%dのダメージ!\n", chara[enemyId].name, (int)damage);
					}
					else // hit = 0
					{
						damage = 0;
						printf("ミス!%sの攻撃は外れてしまった!\n", chara[HERO].name);
					}

					enemyHp -= damage;

					while ((c = getchar()) != '\n');

					break;
				}
				else if (userSelection == '3')
				{
					//回復

					printf("%sは天に祈りをささげた\n", chara[HERO].name);
					if (heroHp == heroHpBuf)
					{
						printf("どこからともなく声が聞こえる・・・\n");
						printf("「お前には私の祝福は必要ないようだ」\n");
						printf("何も起こらなかった!\n");
					}
					else
					{
						rnd = rand() % 100;
						if (rnd <= 40)
						{
							printf("しかし祈りは届かなかった・・・\n");
						}
						else
						{
							heroHp += heroHeal;
							printf("%sに神の祝福が授けられる!\n", chara[HERO].name);
							//最大HPを超えたら戻す
							if (heroHp > heroHpBuf)
							{
								printf("%sのHPが%d回復した!\n", chara[HERO].name, (int)(heroHeal - (heroHp - heroHpBuf)));
								heroHp = heroHpBuf;
							}
							else
							{
								printf("%sのHPが%d回復した!\n", chara[HERO].name, (int)heroHeal);
							}
						}
					}

					while ((c = getchar()) != '\n');

					break;
				}
				else if (userSelection == '4')
				{
					//薬草

					if (heroHp == heroHpBuf)
					{
						printf("%sは薬草を使おうとした\n", chara[HERO].name);
						printf("体中を調べてみたがどこにも傷は見当たらない!\n");
						printf("%sは薬草を袋に戻した・・・\n", chara[HERO].name);
					}
					else
					{
						printf("%sは薬草を使った\n", chara[HERO].name);
						heroHp = heroHpBuf;
						herb--;

						printf("HPが最大値まで回復した\n");
					}

					while ((c = getchar()) != '\n')
						;

					break;
				}
				else
				{
					printText("\n\n人間のできることには限界があるものだ\n");
				}
			}
		}

		//どちらかが倒れたら終了
		if (heroHp <= 0)
		{
			Lose = 1;
			return 0;
		}
		else if (enemyHp <= 0)
		{
			printText("%sをたおした!\n", chara[enemyId].name);
			return 1;
		}
		else if (100 == i)
		{
			printText("ふと気が付くと複数の殺気を感じる。");
			printText("%sの周りを魔物が取り囲んでいる!", chara[HERO].name);
			printText("どうやら時間をかけ過ぎたようだ・・・");
			Lose = 1;
			return 0;
		}


		//敵のターン
		//乱数を出す
		rnd = rand() % 100;
		//HPが1/2以下なら
		if (enemyHp < (enemyHpBuf / 2))
		{
			//半分の確率で回復を実行
			if (rnd < 50)
			{
				printf("%sは冥界の王に祈った!\n", chara[enemyId].name);
				rnd = rand() % 100;
				if (rnd <= 40)
				{
					printf("しかし何も起こらない!");
				}
				else
				{
					printf("%sの体を黒いオーラが包む!\n", chara[enemyId].name);
					enemyHp += enemyHeal;
					//最大HPを超えたら戻す
					if (enemyHp > enemyHpBuf)
					{
						printf("%sのHPが%d回復した!\n", chara[enemyId].name, (int)(enemyHeal - (enemyHp - enemyHpBuf)));
						enemyHp = enemyHpBuf;
					}
					else
					{
						printf("%sのHPが%d回復した!\n", chara[enemyId].name, (int)enemyHeal);
					}
				}

				while ((c = getchar()) != '\n');

			}
			//攻撃
			else
			{
				//物理攻撃が魔法攻撃よりも高くなる場合
				if (enemyAttack > enemyMagic)
				{
					//物理攻撃

					printf("%sの攻撃!\n", chara[enemyId].name);
					//攻撃成功判定
					int hit;
					rnd = rand() % 101;

					//ヒット判定
					if (enemyHit > rnd / 100)
					{
						hit = 1;
					}
					else
					{
						hit = 0;
					}

					//ダメージ計算
					if (enemyAttack < enemyAtkWidth)
					{
						damage = enemyAtkWidth;
					}
					else
					{
						damage = rand() % ((int)enemyAttack - (int)enemyAtkWidth) + enemyAtkWidth;
					}

					//攻撃結果
					if (hit == 1 && damage > 0)
					{
						printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
					}
					else if (hit == 1 && damage <= 0)
					{
						damage = 1;
						printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
					}
					else // hit = 0
					{
						damage = 0;
						printf("ミス!%sの攻撃は外れてしまった!\n", chara[enemyId].name);
					}

					heroHp -= damage;

					while ((c = getchar()) != '\n');
				}
				else
				{
					//魔法
					printf("%sの魔法攻撃!\n", chara[enemyId].name);
					//攻撃成功判定
					int hit;
					rnd = rand() % 101;

					//ヒット判定
					if (enemyHit > rnd / 100)
					{
						hit = 1;
					}
					else
					{
						hit = 0;
					}

					//ダメージ計算
					if (enemyMagic < enemyAtkWidth)
					{
						damage = enemyAtkWidth;
					}
					else
					{
						damage = rand() % ((int)enemyMagic - (int)enemyAtkWidth) + enemyAtkWidth;
					}

					//攻撃結果
					if (hit == 1 && damage > 0)
					{
						printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
					}
					else if (hit == 1 && damage <= 0)
					{
						damage = 1;
						printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
					}
					else // hit = 0
					{
						damage = 0;
						printf("ミス!%sの攻撃は外れてしまった!\n", chara[enemyId].name);
					}

					heroHp -= damage;

					while ((c = getchar()) != '\n');
				}
			}
		}
		else
		{
			//物理攻撃が魔法攻撃よりも高くなる場合
			if (enemyAttack > enemyMagic)
			{
				//物理攻撃

				printf("%sの攻撃!\n", chara[enemyId].name);
				//攻撃成功判定
				int hit;
				rnd = rand() % 101;

				//ヒット判定
				if (enemyHit > rnd / 100)
				{
					hit = 1;
				}
				else
				{
					hit = 0;
				}

				//ダメージ計算
				if (enemyAttack < enemyAtkWidth)
				{
					damage = enemyAtkWidth;
				}
				else
				{
					damage = rand() % ((int)enemyAttack - (int)enemyAtkWidth) + enemyAtkWidth;
				}

				//攻撃結果
				if (hit == 1 && damage > 0)
				{
					printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
				}
				else if (hit == 1 && damage <= 0)
				{
					damage = 1;
					printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
				}
				else // hit = 0
				{
					damage = 0;
					printf("ミス!%sの攻撃は外れてしまった!\n", chara[enemyId].name);
				}

				heroHp -= damage;

				while ((c = getchar()) != '\n');
			}
			else
			{
				//魔法

				printf("%sの魔法攻撃!\n", chara[enemyId].name);
				//攻撃成功判定
				int hit;
				rnd = rand() % 101;

				//ヒット判定
				if (enemyHit > rnd / 100)
				{
					hit = 1;
				}
				else
				{
					hit = 0;
				}

				//ダメージ計算
				if (enemyMagic < enemyAtkWidth)
				{
					damage = enemyAtkWidth;
				}
				else
				{
					damage = rand() % ((int)enemyMagic - (int)enemyAtkWidth) + enemyAtkWidth;
				}

				//攻撃結果
				if (hit == 1 && damage > 0)
				{
					printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
				}
				else if (hit == 1 && damage <= 0)
				{
					damage = 1;
					printf("%sに%dのダメージ!\n", chara[HERO].name, (int)damage);
				}
				else // hit = 0
				{
					damage = 0;
					printf("ミス!%sの攻撃は外れてしまった!\n", chara[enemyId].name);
				}

				heroHp -= damage;

				while ((c = getchar()) != '\n');
			}
		}

		//どちらかが倒れたら終了
		if (heroHp <= 0)
		{
			Lose = 1;
			return 0;
		}
		if (enemyHp <= 0)
		{
			printText("%sをたおした!\n", chara[enemyId].name);
			return 1;
		}

		//次のターンへ
		i++;
	}
	return 0;
}

void BeforeMaouFight()
{
	char c, userSelection;

	while (1)
	{
		printText("\n\n魔王と戦いますか?\n\n");

		printf("1) はい\n");
		printf("2) いいえ\n");

		// ユーザの選択を獲得
		c = getchar();
		userSelection = c;
		while ((c = getchar()) != '\n');
		if ('1' == userSelection) {
			if (0 == strlen(chara[DEVILMAN].name))
			{
				printText("松下「そうか・・・とても残念だよ・・・」");
			}
			else
			{
				printText("%s「さあ、始めよう!」", chara[DEVILMAN].name);
			}
			break;
		}
		else if ('2' == userSelection) {
			printText("%s「俺は・・・戦えない・・・」", chara[HERO].name);
			maouSurrender = 1;
			break;
		}
		else
		{
			printText("決断する時は今だ!");
			//スクリーンをクリア
			system("cls");
		}
	}

}

void main() {
	char c, userSelection;
	int chosedEnemy, i, j;
	FILE *rFile, *wFile;
	//初期化

	//乱数シードの設定
	srand((unsigned)time(NULL));

	while (1) {
		//ゲーム開始時に指定の数値になっていなければならない数値の初期化
		herb = 2;
		playerInNow = 0;
		Lose = 0;
		maouSurrender = 0;
		maouWin = 0;
		maouLose = 0;
		chara[HERO].hp = 5;
		chara[HERO].str = 5;
		chara[HERO].intel = 5;
		chara[HERO].dex = 3;
		chara[HERO].luk = 3;
		//魔王の名前は空でないと困る!
		strcpy(chara[DEVILMAN].name, "");

		//メインメニューの表示
		MainMenu();

		//主人公の名前を入力
		while (1)
		{
			//スクリーンをクリア
			system("cls");

			printf("あなたの名前を教えてください\n");
			fgets(chara[HERO].name, sizeof(chara[HERO].name), stdin);
			chara[HERO].name[strlen(chara[HERO].name) - 1] = '\0';

			while (1)
			{
				if (strlen(chara[HERO].name) == 0)
				{
					system("cls");
					printf("あなたの名前を教えてください\n");

					strcpy(chara[HERO].name, "chara");

					printf("\n\n             %s\n\n", chara[HERO].name);
					printf("これでいいよね?\n");
					printf("1)はい\n");
					printf("2)いいえ\n");
				}
				else if (!(strcmp(chara[HERO].name, "chara")))
				{
					system("cls");
					printf("あなたの名前を教えてください\n");

					printf("\n\n             %s\n\n", chara[HERO].name);
					printf("これでいいよね?\n");
					printf("1)はい\n");
					printf("2)いいえ\n");
				}
				else
				{
					system("cls");
					printf("あなたの名前を教えてください\n");
					printf("%s\n", chara[HERO].name);

					printf("\n\n             %s\n\n", chara[HERO].name);
					printf("こちらでよろしいですか?\n");
					printf("1)はい\n");
					printf("2)いいえ\n");
				}

				c = getchar();
				userSelection = c;
				while ((c = getchar()) != '\n')
					;

				if (userSelection == '1' || userSelection == '2')
				{
					break;
				}
				else
				{
					printf("選択肢は二つだ\n");
					while ((c = getchar()) != '\n');

					//スクリーンをクリア
					system("cls");
				}
			}

			//「1」を選んでいたらbreak
			if (userSelection == '1')
			{
				break;
			}
		}


		FirstStory();

		forwordDungeon();
		printStory(SLIME);
		if (fight(SLIME))
		{
			changeStatus();
			forwordDungeon();
			printStory(PISORO);
			if (fight(PISORO))
			{
				changeStatus();
				forwordDungeon();
				printStory(GOLEM);
				if (fight(GOLEM))
				{
					changeStatus();
					forwordDungeon();
					printStory(DRAGON);
					if (fight(DRAGON))
					{
						changeStatus();
						forwordDungeon();
						//ランダムで敵を選ぶ
						chosedEnemy = rand() % 4 + 5;
						printStory(chosedEnemy);
						if (fight(chosedEnemy))
						{
							changeStatus();
							//魔王をファイルから呼び出す
							rFile = fopen(file_name, "r");
							if (NULL == rFile)
							{//魔王が呼び出せなかったら
								forwordDungeon();
								printStory(MATUSHITA);
								BeforeMaouFight();

								if (!(maouSurrender))
								{
									if (fight(MATUSHITA))
									{
										maouLose = 1;
									}
									else
									{
										maouWin = 1;
									}
								}
							}
							else
							{//魔王が呼び出せたら
								char read[256];

								fgets(read, sizeof(read) - 1, rFile);

								strcpy(chara[DEVILMAN].name, strtok(read, ","));
								chara[DEVILMAN].hp = atoi(strtok(NULL, ","));
								chara[DEVILMAN].str = atoi(strtok(NULL, ","));
								chara[DEVILMAN].intel = atoi(strtok(NULL, ","));
								chara[DEVILMAN].dex = atoi(strtok(NULL, ","));
								chara[DEVILMAN].luk = atoi(strtok(NULL, ","));
								winCount = atoi(strtok(NULL, ","));

								//読み込みファイルを閉じる
								fclose(rFile);
								forwordDungeon();
								printStory(DEVILMAN);
								BeforeMaouFight();

								if (fight(DEVILMAN))
								{
									maouLose = 1;
								}
								else
								{
									maouWin = 1;
								}
							}
						}
					}
				}
			}
		}

		// 勝利か敗北のメッセージでゲーム終了する
		system("cls");

		printf("*************\n");
		printf("* GAME OVER *\n");
		printf("*************\n\n");

		if (Lose) {
			printText("その後%sの姿を見たものはいなかった・・・", chara[HERO].name);
		}
		if (maouSurrender && 0 == strlen(chara[DEVILMAN].name))
		{
			printText("%sは学校を卒業し、無事に役所への就職を果たした!\nだがなぜか心の中には虚しさが残るのだった・・・", chara[HERO].name);
		}
		if (maouWin) {
						while (fgets(readBuf, sizeof(readBuf) - 1, rFile) != NULL)
			if (0 == strlen(chara[DEVILMAN].name))
			{
				printText("松下「こうなることは分かっていた・・・」");
			}
			else
			{
				winCount++;

				if (3 == winCount)
				{
					//読み込みファイルを開く
					rFile = fopen(file_nameLEGEND, "r");
					if (NULL == rFile)
					{//殿堂入りがいなかったら
						//書き込みファイルを開く
						wFile = fopen(file_nameLEGEND, "w");
						fprintf(wFile, "★殿堂入り★ (WINは0で固定)\n");
						fprintf(wFile, "%s,%d←HP,%d←STR,%d←INT,%d←DEX,%d←LUK,%d←WIN\n", chara[DEVILMAN].name, chara[DEVILMAN].hp, chara[DEVILMAN].str, chara[DEVILMAN].intel, chara[DEVILMAN].dex, chara[DEVILMAN].luk, 0);
					}
					else
					{//殿堂入りがあったら
						char log[20][256] = { 0 };
						char readBuf[256] = { 0 };
						//ファイルの中身を読み込む
						i = 0;
						{
							strcpy(log[i], readBuf);
							i++;
						}
						//読み込みファイルを閉じる
						fclose(rFile);

						//書き込みファイルを開く
						wFile = fopen(file_nameLEGEND, "w");
						fprintf(wFile, "★殿堂入り★ (WINは0で固定)\n");
						fprintf(wFile, "%s,%d←HP,%d←STR,%d←INT,%d←DEX,%d←LUK,%d←WIN\n", chara[DEVILMAN].name, chara[DEVILMAN].hp, chara[DEVILMAN].str, chara[DEVILMAN].intel, chara[DEVILMAN].dex, chara[DEVILMAN].luk, 0);

						j = 1;
						while (j <= 9)
						{
							fputs(log[j], wFile);
							j++;
						}
					}
					//書き込みファイルを閉じる
					fclose(wFile);
					//maou.txtファイルを削除
					remove(file_name);
				}
				else
				{//魔王の勝利数を更新
					//書き込みファイルを開く
					wFile = fopen(file_name, "w");
					fprintf(wFile, "%s,%d←HP,%d←STR,%d←INT,%d←DEX,%d←LUK,%d←WIN", chara[DEVILMAN].name, chara[DEVILMAN].hp, chara[DEVILMAN].str, chara[DEVILMAN].intel, chara[DEVILMAN].dex, chara[DEVILMAN].luk, winCount);
					//書き込みファイルを閉じる
					fclose(wFile);
				}
				printText("%s「初めからこうなる運命だったのさ!」", chara[DEVILMAN].name);
			}
		}
		if (maouLose) {
			printText("こうして確かに魔王は倒された。だが、%sの行方は誰も知らない・・・", chara[HERO].name);
			//書き込みファイルを開く
			wFile = fopen(file_name, "w");
			fprintf(wFile, "%s,%d←HP,%d←STR,%d←INT,%d←DEX,%d←LUK,%d←WIN", chara[HERO].name, chara[HERO].hp, chara[HERO].str, chara[HERO].intel, chara[HERO].dex, chara[HERO].luk, 0);
			//書き込みファイルを閉じる
			fclose(wFile);
		}
	}
}
