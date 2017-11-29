//
//  JNA_Functions.cpp
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#include "JNA_Functions.h"

double e1(double w[]);
double e2(double w[]);

/// JNA interface function.
double evaluateFcns(double individual[], int func_index)
{
	double fitness = 0.0;
	switch(func_index)
	{
	case 1:
		fitness = e1(individual);
		break;
	case 2:
		fitness = e2(individual);
		break;
	default:
		break;
	}
	return fitness;
}

double e1(double w[])
{
	ANNWeights* arbi = new ANNWeights({6, 10, 3}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w1 = new ANNWeights({17, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w2 = new ANNWeights({14, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w3 = new ANNWeights({11, 20, 2}, {false, true, false}, {false, true, true}, true);

	arbi->Randomize();
	//w1->Randomize();
	w2->Randomize();
	w3->Randomize();

	w1->Set(w);

	double fitness = 0.0;

	for(int i = 0; i < 3; i++) {
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		b2World* world = new b2World(gravity);
		J1_S_Field::Configuration fc;
		fc.MaxStep = 12000;
		fc.World = world;
		fc.TrainingMode = 1;
		J1_M_M1 monitor;

		assa2d::SceneMgr* scenemgr = new J1_S_Field(&fc, arbi, w1, w2, w3);
		scenemgr->Run(&monitor);

		delete scenemgr;
		delete world;

		fitness += monitor.GetFitness();
	}
	fitness /= 3.0f;

	delete arbi;
	delete w1;
	delete w2;
	delete w3;

	return fitness;
}

double e2(double w[])
{
	ANNWeights* arbi = new ANNWeights({6, 10, 3}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w1 = new ANNWeights({17, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w2 = new ANNWeights({14, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w3 = new ANNWeights({11, 20, 2}, {false, true, false}, {false, true, true}, true);

	double w1_c[802] = {-0.5383318550524318, -0.552280780898518, 0.5276983290847641, -0.3066112027118247, 0.7601140723689316, 0.2613273651212995, -0.6152172848799514, 0.3594026057556143, 0.18829342385566694, -0.3535629745702894, -0.6978253282870222, 0.46293381063819194, -0.9811246974343053, 0.6347409579386409, 0.35872609628383084, -0.2591893879070061, 0.5405880711768117, -0.5160558633513765, 0.5281854640772115, -0.10469412617188575, -0.7147905940566235, -0.2664727583131597, 0.4020884850196755, 0.07702046824670346, 0.6798664014565856, -0.12107104671361825, -0.7579669177628928, 0.0980351580047083, 0.23888707131104994, -0.5254538601492579, -0.8300776817138755, 0.6379324666943706, -0.5449103883305176, 0.027675107339835508, 0.6780943695961322, -0.1281101371978856, 0.5588831613789372, -0.1035757141753926, -0.3958608357050433, 0.04401733030261983, 0.11567658225636106, 0.13240511673943545, 0.06375554360093712, -0.7336841406579317, -0.5702546804974951, 0.4910077697922703, 0.31791904227352563, -0.36752274443505384, 0.6031021470563094, 0.1702961688742622, -0.3148066077570187, 0.5291938695787837, 0.20962214676090798, 0.2897594326638796, 0.052345808123244186, -0.39836360236971113, 0.079229636706903, 0.7434466708134706, 0.0782252826768477, -0.24128248817007025, 0.5486728035803912, 0.03979400284011593, -0.4545042782882409, 0.3792648338045432, -0.5855355818279333, 0.3321685980730087, 0.7492403907965488, -0.3918795027436165, 0.3649995267251731, 0.2719406525479245, 0.06716875960155218, -0.8256755009242852, 0.5280995357405037, -0.7345392805408243, -0.18036395463866142, 0.49882872747503976, -0.4467469092508053, 0.2235058967399831, -0.1600987026578243, 0.45799081291294175, 0.5836730843453717, 0.2689509540097941, -0.6147960886876985, -0.5392411861817231, -0.782159104572294, -0.19957551475671245, 0.10671174072325304, -0.09752377611874939, 0.250734625273073, 0.10806985215846501, 0.5929787981873875, -0.19273152954251258, 0.4820289291456533, -0.3014721221823289, -0.44351938626823023, 0.7455132463817106, -0.1424173402018411, 0.7431466848516135, -0.3817944285201955, 0.42053820081942156, 0.589067122027214, -0.34037712281284777, -0.03570038593197733, -0.2517594490998846, 0.6823016360338803, -0.49766310572922606, 0.4760969332195333, -0.1255505746444162, -0.21147649969560525, -0.20621305680750981, 0.08435137352117474, 0.19827699320535003, 0.4107486125736667, -0.14180589186598153, -0.12872456205923208, 0.4275197676230251, -0.23166583910183172, 0.5074312419047085, -0.5424540851349111, 0.2740043981262733, -0.6477324120687324, 0.327904384154149, 0.254511906294912, 0.24613341524822244, 0.4659639003070413, -0.09218218835930497, -0.48426568409782167, 0.6003147020326636, 0.002148302416860731, -0.23150263640434812, -0.32606634493501996, 0.7765964570062197, -0.856727619865881, 0.46622111063311883, -0.20605602480421237, -0.11940423565349748, 0.320790401635523, -0.23034108066379777, -0.22498496344420227, 0.26285419530884135, -0.22765423159071616, -0.025790802796137345, 0.20561058116616612, 0.5953095623358828, 0.05992087642166086, 0.738722177115446, -0.520651425298088, 0.13587804231235118, 0.37736102697881385, 0.411967565721307, -0.698336292503434, 0.3081404696239311, -0.6835824356897298, 0.05665360737470885, 0.4297970204888235, 0.0962618933028054, 0.3880564954455318, -0.34245313581532705, -0.21299960662507456, 0.6075192289615983, -0.20795624789250838, -0.6083421998658239, 0.7003674686845501, -0.20142868639243527, 0.47588320990238336, 0.7093115325927437, 0.09026833377110219, 0.2403470879901057, 0.1659583574918496, 0.5782671476061807, -0.1496974301402885, 0.17837814023998447, -0.748969553561746, -0.2730903450826031, 0.7433287318507911, 0.7511784413929725, 0.4076505578022933, 0.15721362528702237, 0.6848472118031943, 0.1706724010978567, -0.14044537450295191, -0.23459363601069583, -0.555839427816674, -0.3368087469646092, -0.4655513059024259, 0.41186881594726904, 0.7265906775180335, 0.43320078777776005, 0.06470892287039487, 0.7919686937983208, 0.06432637706596395, -0.5497622003624976, 0.6017678348499241, -0.7574904639499973, -0.4121823696885173, 0.3656909006817629, -0.23210381492177587, 0.6900460207977954, -0.5326373178482666, 0.008758523038209176, 0.5086904458149657, -0.2857481382470794, -0.13798839794323198, 0.4867099214552539, 0.6072917353023333, 0.6023616020973535, -0.29879891858794677, 0.08140699261839106, 0.32541061216535433, -0.017361991460423852, -0.48883510013641684, 0.4809841460082451, -0.6536219499135508, -0.20934098845171384, -0.25426862098140524, -0.188418881341412, -0.653442931438816, -0.29424491483362203, 0.41710031315952795, 0.021992081320004103, 0.5547689699890661, -0.22671277066170537, 0.7315124824819704, -0.050823392562113934, -0.040703934454057886, 0.33985649684985036, -0.06451923934484953, 0.1306584205286753, -0.29490270504564253, 0.31415231270329375, 0.08240266523995858, -0.19043349112699154, 0.21216420965717472, 0.4310392080343928, -0.39075760131074594, 0.7112441110393165, -0.27748862614305325, 0.15075111495747479, 0.3995154538709077, 0.3567089866521549, 0.5601369383984567, -0.3113671282481116, -0.08926788478913911, -0.46722927441234924, -0.08858024931009678, 0.038134628848046644, 0.6052591340454977, -0.8039258819283217, -0.2554108497575035, 0.6074532085575002, 0.5616389123715371, -0.4451111953432648, 0.6790206211563542, -0.5921436457655905, -0.03707443085828534, -0.07213559033489514, -0.26756936064913683, 0.7500032452606502, -0.3370622685520735, 0.5574234452899258, 0.25294444461990545, -0.02479728326156752, -0.10932471235110022, 0.20404586731871208, 0.1867565539677653, 0.6781794341275043, -0.011181043777065525, 0.423369447279243, 0.4076968784504889, 0.4146102055140694, -0.3039137221039602, 0.27102119772808053, 0.44046699808623146, -0.04704687540421021, -0.5364428005272583, 0.6104141970475098, -0.3272183322594377, 0.0733448995383543, 0.6030639557549576, -0.28630298338615856, 0.4250361661057059, 0.07143148292673904, -0.07636497297660569, -0.014850558304858881, -0.04373007897637163, 0.24035085806885312, -0.10058295436975076, 0.7059570882600854, 0.2589111872933654, -0.246675164345634, 0.4662993553036461, -0.46527362963794455, 0.11294080787350053, -0.22472952623395448, -0.5279907846218286, -0.24133327841483995, -0.33173397377456415, -0.3575886206301659, -0.15160659998504053, 0.6109878288305547, 0.19311307658211047, -0.01149412833926887, 0.10105154388066985, -0.3891774530688502, -0.10564880756967096, -0.6470903296798626, 0.7411657525276245, 0.4508562331868079, 0.18466119441794354, 0.6668353048538621, 0.5760654299541685, 0.31479755950166904, 0.3237687703863059, -0.0993687849203463, -0.04795977728322446, -0.5187245237048488, -0.3865420208320528, -0.3713812845519714, -0.14367910610596446, -0.07783380312257442, -0.1918747356314594, -0.3171086772010022, -0.5445726891826106, -0.6384920865711261, -0.8305497961152835, 0.2044042998851627, -0.6298790139009793, -0.20162575060875618, 0.3013003089521654, 0.6280548094372739, 0.6159330597221845, 0.15369601765142654, 0.5262494266156428, -0.5849268285750147, -0.47072020632764566, 0.5510276715598651, 0.06915371505317522, 0.3289717949197142, -0.4984030864191481, -0.18228120752804727, 0.6499198327435038, -0.32613867396613405, -0.7297880759768022, -0.6422232421531628, 0.7513122306286519, 0.33441592467346254, -0.2703372729507677, -0.6170399396029794, 0.3786459050849683, 0.4680879953637229, 0.8541536590799846, -0.3054755199079123, 0.3652761663919859, -0.44947362245737577, 0.5435966351062156, 0.18587977017597054, 0.7239792414650086, -0.3956833607917441, 0.6836061099482615, -0.6725778366950231, -0.37403484457919356, -0.540291830654789, 0.2310021191589035, 0.7852668727018688, -0.6972394993023202, -0.5001820300306898, -0.4727189990146261, 0.12188550076433992, -0.6538455354527701, 0.41425476477374756, 0.4812357567937291, 0.215542201228056, 0.2968339325461691, 0.7508312925378514, 0.4814855573061628, 0.02390417577406239, 0.3925850315300465, 0.6663573112269198, 0.4523781195601761, -0.07506820337510546, 0.06902128796389748, 0.03464239145674231, 0.18045190421021726, 0.3895228344886337, -0.6117377425361262, 0.17536507010883678, 0.07618931094609738, 0.3127307086989658, -0.023557778622376666, 0.416968104565793, 0.47435151540329573, -0.6343480103409945, -0.17354039135784532, 0.280228850153523, -0.0343617810730462, 0.12403926385598747, -0.3028161471805021, 0.056769529258958396, -0.5637004774871543, -0.3709101738608866, -0.5930690142860204, -0.6334185324517032, -0.1274909009667742, 0.18588325704597758, -0.5508756582059898, 0.160436654198072, 0.3384088561362669, 0.01898643916941417, 0.43616296871188726, -0.548997764940457, 0.3752443371737512, 0.31402863861459446, -0.422733702426854, 0.4912376701680199, 0.14816032286762437, -0.019841593126018367, 0.4111161204176072, -0.05572758270961344, -0.5792316703674741, 0.37998162782332795, -0.05519606193244454, -0.11981013445423032, -0.09327995395321154, 0.04608062138227975, 0.6094147067726003, 0.3888529434573269, -0.3670069876633176, 0.34424189586857534, -0.6816188818709881, -0.173116765865359, 0.7939536758872792, 0.2991545207491393, -0.21049900421429452, 0.24058285719163153, -0.5464243191504656, -0.323194548480894, 0.06429757338321934, 0.02008753660114416, 0.17698742719682173, 0.2703221511458711, 0.3929004785539668, -0.1968580589291198, -0.4296500099519816, 0.3567440592112652, -0.08474349531507587, 0.20652192306009542, -0.12622027907692088, -0.23784227401919927, -0.2678222312280535, -0.6242618224640556, -0.5410828353698491, 0.7126870258106361, -0.6119050854746859, 0.23804853179158558, 0.6479360277115259, -0.2209304035533569, -0.41852151280808036, -0.8842389102975949, -0.6417435723601305, 0.40835221494314533, 0.7433803413555066, -0.7415529752120529, 0.42327524997360316, -0.6231103095065704, -0.3595527447611706, 0.032696144894802874, -0.6426129259673595, 0.8601629380191584, 0.007768524513201806, -0.26368422652500795, -0.6114562717162022, 0.02576497161191342, -0.5339429152332918, 0.05171225841397176, 0.41523933319539025, -0.5828340797854168, 0.3895152639897231, -0.03413273105257716, -0.3060532222284776, -0.34221091431699024, -0.4173675011770319, -0.21201797969506653, 0.2629032908278989, 0.12283739643774852, 0.36428256927909014, 0.13036312686607807, -0.27721786310600116, 0.16086608635473304, 0.2255226298971476, 0.007909289126781184, 0.5021660457506615, 0.415037568232726, 0.5482920209744673, -0.2539261106702882, -0.09023648172391488, -0.2683682068225596, 0.4477881830759557, -0.09977696754175264, 0.5830244173263238, 0.7781733970657748, 0.10561218618671381, -0.45861622738204816, -0.3627408696688536, 0.481792747331957, -0.3725432292531568, 0.2631324904173051, 0.051204929054195464, 0.5155745171063348, -0.02488649513763457, 0.5290328051453135, 0.5316102910912738, -0.09971896527036046, 0.2259990555327252, 0.26311348022496667, -0.555035227904403, -0.5546880277286544, -0.412390403242952, 0.28412704854417603, -0.29216405618543806, 0.0793428184213121, 0.10999005998451193, -0.1798804183167968, 0.7076901592273019, 0.1169754206858663, -0.22978214008361394, -0.24746109953147136, 0.006141005840368842, 0.1293328898116609, -0.08347071736435155, -0.37700659071116804, -0.3186396665739472, 0.31449685817936135, 0.017272955737746946, -0.19836197910834427, 0.18393873684563025, -0.3058959926867701, -0.11714890103393823, -0.4941533163919817, 0.8057510421497743, 0.36374966678285303, 0.04130749011727998, 0.201635378084519, 0.438392821403535, 0.43886130774753973, 0.04846634700404272, 0.8392518671032463, -0.1235396265414449, 0.12055338201836359, 0.3629283943750419, 0.1970292731886715, 0.499365238212004, 0.03760834184508824, -0.7067667033694884, -0.8066778342660229, -0.4308011312437481, 0.6020428812846846, 0.4389228879092982, -0.14690065818096876, 0.2897057855718504, -0.7042790053557328, 0.7711960881301384, -0.5379580022911087, -0.2018128356176155, -0.17081548714865574, -0.15596548066080065, 0.6923645473976351, 0.7329412080568354, 0.3092781873871654, 0.17125753372266633, 0.23179640434237497, 0.12834240056668503, 0.260577649067465, 0.4504445780380157, -0.6661376092946809, 0.6684539777999954, 0.2782521005741221, -0.01886432305287107, -0.3082769118488725, 0.01298601150971632, 0.5418238476737571, 0.5099998070238497, 0.22752667375316457, 0.0505523142611711, 0.5090374423690226, -0.3292736031794673, -0.3230405104657308, 0.4050418020558126, -0.38921352721361563, 0.16550032505691994, -0.18859508281856313, 0.4696079620831977, -0.26936492445412324, 0.7547446822543538, -0.02674412511694796, 0.2509172662436723, -0.15195463957719724, -0.4563459170144241, 0.19649751822540037, -0.7484346324719223, 0.5281316713069102, 0.059642604799649133, -0.10183825031109871, 0.3196694604939758, -0.7228020806363732, 0.4014057668468208, 0.13571636489573685, -0.7179817256201352, 0.6984352739288995, -0.42978698961527845, 0.04360343777661316, -0.4582036763332717, 0.6339192589726935, -0.7421864101456853, -0.4739676741243507, 0.42608754281285116, -0.08498947715535143, -0.45800073651985374, 0.6735049593072104, 0.7366425200567274, 0.4919459083228832, 0.5235640057145438, -0.054507538906969785, 0.009174386766226124, -0.15518218626709548, -0.01651326923950342, 0.4017098281695211, 0.5066411599538257, 0.4188426149804656, 0.5974539899812112, 0.20496235415209588, 0.7118949683045632, -0.07456744730669765, 0.2981010693998022, -0.5391596132738425, -0.37464448985747945, -0.2981451618793528, -0.4116303142623123, 0.08066968801191443, -0.6122587170664219, -0.05414807767891004, -0.022986969279620646, 0.23151855274455616, 0.5338098729671338, 0.09443937025151156, 0.23088169823880011, 0.3392633893736868, -0.3242540908112244, 0.5258111054534909, -0.6992941762214995, -0.8212171567084549, -0.27076450634608273, 0.5408692662468889, -0.3559313125122121, -0.2645021741924425, 0.015033748888017767, 0.588529576424986, -0.003661824841217201, -0.271972923713539, -0.07371117754659562, -0.05122139048384196, 0.10938462162693582, 0.28689122516400967, 0.7980127087116715, -0.32634840963090184, -0.43870940809331893, -0.266170947125545, -0.33611130430681146, -0.13156743099140422, -0.30851440179491946, 0.03226291431520979, -0.1917208596040377, 0.9237629827514386, 0.2496076912476085, -0.2027823789997876, -0.15003521281206336, -0.28120331293271106, 0.41330663972895476, 0.3814607200949667, -0.40413391701477747, 0.08787197178310624, -0.11694516483583751, 0.5602315695362242, -0.23222681328095726, 0.586875209231586, -0.09596273978228057, 0.6831374955374633, -0.028748474635337973, -0.23834071185402186, 0.4611044708188562, 0.3769481260134684, -0.4032044119890438, 0.1358420156495169, 0.7052862921983621, 0.11993612709787566, -0.8292062821834044, -0.49232316850491825, 0.46912970021418093, -0.24982463466920096, -0.2635900131072077, -0.21816770538609342, -0.6017913752498419, -0.10234448654688658, 0.20286650518501287, -0.21628550241440553, 0.7716247663481821, -0.30889063993582083, 0.2858643102593481, 0.20537498517765435, -0.16168970375041208, -0.2790597339250512, 0.17697677762986577, 0.6303354446007894, -0.3776040175714055, -0.5032022863154654, 0.6221294333661285, -0.4115094735406746, -0.007901429101264103, 0.6104140446967958, 0.3013899782450172, 0.18795265940376582, -0.7824111936254428, -0.6668783903893991, 0.3961140356523551, -0.4223861921399454, -0.7231279921829096, -0.3490329138930019, -0.03364568389282743, -0.43049818753263325, 0.22299863140783027, -0.23078517543847324, 0.6282434931905725, -0.6647969360969819, 0.2226017368504337, -0.6126383098968509, -0.2970454586873774, -0.6920391186233509, -0.2967455494705781, 0.46809945203663017, -0.18482379030560475, 0.34046120981755346, -0.16317396914649837, -0.5543167120786915, -0.143462352288587, -0.7206779396400764, -0.19549611490480462, 0.1817468766581421, 0.25482195379740286, -0.19187184143768626, -0.4521339439803542, -0.014460372671130484, -0.22710125017642036, 0.5707057332021709, -0.15855311029965513, -0.3227786458294303, 0.775923105528597, -0.10376273761315691, 0.11646602018295252, 0.6674337222110956, -0.4879508289089917, 0.09605982622753537, 0.41230074941499045, -0.2508907962967635, -0.33920649174680406, -0.49018898859565385, -0.23484940804286625, -0.3329891465351131, 0.6359330716724652, 0.5747638985144711, 0.1961132767159589, -0.13596061378560323, -0.16848130256709457, 0.29082665097375704, 0.11905731997275665, 0.3442894831393728, -0.3962858684614612, 0.17012880165642585, -0.17428010551863726, 0.3125031494214177, -0.08213187970204709, 0.23112885865275667, -0.2530727946637524, -0.07291300570878366, 0.3141882435490712, 0.3805472049946551, -0.23325334771666895, 0.2959319629859877, -0.2115014479690747, -0.37337327243018587, 0.007994250368682482, -0.03538779310455649, 0.011979805877338465, 0.126535303470749, -0.09651560690517694, 0.1769240619234447, -0.09769943665960668, -0.009291459193227476, -0.2016887888338025, 0.2518465996027534, -0.1390702321913963, 0.20500524242942736, -0.22688395977855375, 0.11680856563540001};
	w1->Set(w1_c);

	w2->Set(w);

	arbi->Randomize();
	w3->Randomize();

	double fitness = 0.0;
	for(int i = 0; i < 3; i++) {
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		b2World* world = new b2World(gravity);
		J1_S_Field::Configuration fc;
		fc.MaxStep = 12000;
		fc.World = world;
		fc.TrainingMode = 2;
		J1_M_M2 monitor;

		assa2d::SceneMgr* scenemgr = new J1_S_Field(&fc, arbi, w1, w2, w3);
		scenemgr->Run(&monitor);

		delete scenemgr;
		delete world;

		fitness += monitor.GetFitness();
	}
	fitness /= 3.0f;

	delete arbi;
	delete w1;
	delete w2;
	delete w3;

	return fitness;
}
