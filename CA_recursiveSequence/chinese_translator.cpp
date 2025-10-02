#include "chinese_translator.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveChineseVersion() {
	ofstream outFile("RecursiveSequence_ChineseVersion.txt");

	if (!outFile.is_open()) {
		cout << "Error: Could not create Chinese translation file.\n";
		return;
	}

	// Write UTF-8 BOM for proper Chinese character display
	outFile << "\xEF\xBB\xBF";

	outFile << "================================================================\n";
	outFile << "     递归序列求解器 - 教育版                                     \n";
	outFile << "================================================================\n\n";

	outFile << "欢迎！本程序将教您如何求解递归序列并找到捷径（闭式公式）。\n";
	outFile << "如果您不是数学专家，请不要担心 - 我们将一步步解释所有内容！\n\n";

	outFile << "================================================================\n";
	outFile << "步骤 1: 理解问题\n";
	outFile << "================================================================\n\n";

	outFile << "什么是递归序列？\n";
	outFile << "把它想象成一个连锁反应：\n";
	outFile << "  - 您从一个数字开始（第一项）\n";
	outFile << "  - 使用一个公式（配方）来获得下一个数字\n";
	outFile << "  - 一遍又一遍地重复这个过程\n\n";

	outFile << "我们的具体问题：\n";
	outFile << "  起始点: a(1) = 4\n";
	outFile << "  递推公式: a(n+1) = (4 * a(n) - 1) / (a(n) + 2)\n\n";

	outFile << "用简单的话说：\n";
	outFile << "  '要得到下一项，取当前项，乘以4，减去1，\n";
	outFile << "   然后除以当前项加2。'\n\n";

	outFile << "挑战：\n";
	outFile << "  如果我们想求 a(1000) 怎么办？\n";
	outFile << "  使用递推公式，我们需要先计算 999 项！\n";
	outFile << "  这太慢太麻烦了。\n\n";

	outFile << "目标：\n";
	outFile << "  找到一个捷径公式，让我们直接跳到任意项！\n";
	outFile << "...找到捷径公式（" << "闭式公式" << "）\n";

	outFile << "================================================================\n";
	outFile << "步骤 2: 慢速方法（递归计算）\n";
	outFile << "================================================================\n\n";

	outFile << "让我们使用递推公式手动计算前5项：\n\n";

	outFile << "第1项: a(1) = 4（已知）\n";
	outFile << "  --> 我们从这里开始！\n\n";

	outFile << "第2项: a(2) = (4 * a(1) - 1) / (a(1) + 2)\n";
	outFile << "             = (4 * 4 - 1) / (4 + 2)\n";
	outFile << "             = (16 - 1) / 6\n";
	outFile << "             = 15 / 6\n";
	outFile << "             = 2.5\n";
	outFile << "  --> 我们用 a(1) 得到 a(2)\n\n";

	outFile << "第3项: a(3) = (4 * a(2) - 1) / (a(2) + 2)\n";
	outFile << "             = (4 * 2.5 - 1) / (2.5 + 2)\n";
	outFile << "             = (10 - 1) / 4.5\n";
	outFile << "             = 9 / 4.5\n";
	outFile << "             = 2.0\n";
	outFile << "  --> 我们用 a(2) 得到 a(3)\n\n";

	outFile << "第4项: a(4) = (4 * 2.0 - 1) / (2.0 + 2)\n";
	outFile << "             = (8 - 1) / 4\n";
	outFile << "             = 7 / 4\n";
	outFile << "             = 1.75\n\n";

	outFile << "第5项: a(5) = (4 * 1.75 - 1) / (1.75 + 2)\n";
	outFile << "             = (7 - 1) / 3.75\n";
	outFile << "             = 6 / 3.75\n";
	outFile << "             = 1.6\n\n";

	outFile << "注意问题所在：\n";
	outFile << "  - 要得到 a(5)，我们需要 a(4)\n";
	outFile << "  - 要得到 a(4)，我们需要 a(3)\n";
	outFile << "  - 要得到 a(3)，我们需要 a(2)\n";
	outFile << "  - 要得到 a(2)，我们需要 a(1)\n\n";

	outFile << "这就像爬楼梯 - 您必须踩在每一个台阶上！\n";
	outFile << "对于 a(100)，您需要先计算 99 项。太糟糕了！\n\n";

	outFile << "================================================================\n";
	outFile << "步骤 3: 侦探工作 - 寻找规律\n";
	outFile << "================================================================\n\n";

	outFile << "让我们把计算出的项写成分数形式：\n\n";

	outFile << "  a(1) = 4   = 4/1\n";
	outFile << "  a(2) = 2.5 = 5/2\n";
	outFile << "  a(3) = 2.0 = 6/3\n";
	outFile << "  a(4) = 1.75 = 7/4\n";
	outFile << "  a(5) = 1.6 = 8/5\n\n";

	outFile << "嗯...让我们看看分子（上面的数字）：\n";
	outFile << "  4, 5, 6, 7, 8...\n";
	outFile << "  --> 它们每次增加1！\n\n";

	outFile << "再看看分母（下面的数字）：\n";
	outFile << "  1, 2, 3, 4, 5...\n";
	outFile << "  --> 它们就是自然数！\n\n";

	outFile << "啊哈！发现规律了：\n";
	outFile << "  分子 = n + 3\n";
	outFile << "  分母 = n\n\n";

	outFile << "让我们验证：\n";
	outFile << "  n=1: 分子 = 1+3 = 4, 分母 = 1  --> 4/1 ✓\n";
	outFile << "  n=2: 分子 = 2+3 = 5, 分母 = 2  --> 5/2 ✓\n";
	outFile << "  n=3: 分子 = 3+3 = 6, 分母 = 3  --> 6/3 ✓\n";
	outFile << "  n=4: 分子 = 4+3 = 7, 分母 = 4  --> 7/4 ✓\n";
	outFile << "  n=5: 分子 = 5+3 = 8, 分母 = 5  --> 8/5 ✓\n\n";

	outFile << "太好了！我们找到了捷径公式：\n\n";
	outFile << "       a(n) = (n + 3) / n\n\n";

	outFile << "================================================================\n";
	outFile << "步骤 4: 快速方法（闭式公式）\n";
	outFile << "================================================================\n\n";

	outFile << "现在我们有了神奇的公式：a(n) = (n + 3) / n\n\n";

	outFile << "让我们测试一下！我们将计算 a(100)：\n\n";

	outFile << "旧方法（递归）：\n";
	outFile << "  a(100) = 使用 a(99)\n";
	outFile << "  a(99) = 使用 a(98)\n";
	outFile << "  ...\n";
	outFile << "  （需要99次计算！）\n\n";

	outFile << "新方法（闭式公式）：\n";
	outFile << "  a(100) = (100 + 3) / 100\n";
	outFile << "         = 103 / 100\n";
	outFile << "         = 1.03\n";
	outFile << "  （只需1次计算！）\n\n";

	outFile << "让我们试试更大的数 - a(985)：\n";
	outFile << "  a(985) = (985 + 3) / 985\n";
	outFile << "         = 988 / 985\n";
	outFile << "         = 1.00304568...\n\n";

	outFile << "立即得出结果！不需要先计算 984 项！\n\n";

	outFile << "为什么这样有效：\n";
	outFile << "  递推公式隐藏了一个简单的规律。\n";
	outFile << "  通过计算几项并寻找规律，我们发现了捷径！\n\n";

	outFile << "额外见解：\n";
	outFile << "  注意：随着 n 变大，a(n) 越来越接近 1\n";
	outFile << "  a(10) = 13/10 = 1.3\n";
	outFile << "  a(100) = 103/100 = 1.03\n";
	outFile << "  a(1000) = 1003/1000 = 1.003\n";
	outFile << "  a(无穷大) 趋近于 1！\n\n";

	outFile << "================================================================\n";
	outFile << "步骤 5: 为什么有效（数学证明）\n";
	outFile << "================================================================\n\n";

	outFile << "如果您想理解数学证明，请继续阅读。\n";
	outFile << "否则，只需知道我们的公式是正确的！\n\n";

	outFile << "--- 数学证明 ---\n\n";

	outFile << "我们使用一个巧妙的替换技巧：\n\n";

	outFile << "1. 令 b(n) = a(n) - 1\n";
	outFile << "   （我们将序列向下移动1）\n\n";

	outFile << "2. 那么 a(n) = b(n) + 1\n\n";

	outFile << "3. 代入原始公式：\n";
	outFile << "   a(n+1) = (4*a(n) - 1) / (a(n) + 2)\n";
	outFile << "   b(n+1) + 1 = (4*(b(n) + 1) - 1) / ((b(n) + 1) + 2)\n";
	outFile << "   b(n+1) + 1 = (4*b(n) + 3) / (b(n) + 3)\n\n";

	outFile << "4. 求解 b(n+1)：\n";
	outFile << "   b(n+1) = (4*b(n) + 3) / (b(n) + 3) - 1\n";
	outFile << "   b(n+1) = (4*b(n) + 3 - b(n) - 3) / (b(n) + 3)\n";
	outFile << "   b(n+1) = (3*b(n)) / (b(n) + 3)\n\n";

	outFile << "5. 计算 b(1)：\n";
	outFile << "   b(1) = a(1) - 1 = 4 - 1 = 3\n\n";

	outFile << "6. 通过模式识别（或数学归纳法），\n";
	outFile << "   我们可以证明 b(n) = 3/n\n\n";

	outFile << "7. 转换回 a(n)：\n";
	outFile << "   a(n) = b(n) + 1\n";
	outFile << "   a(n) = 3/n + 1\n";
	outFile << "   a(n) = (3 + n) / n\n";
	outFile << "   a(n) = (n + 3) / n  ✓\n\n";

	outFile << "这就是我们如何证明公式是正确的！\n\n";

	outFile << "================================================================\n";
	outFile << "总结 - 您学到了什么\n";
	outFile << "================================================================\n\n";

	outFile << "1. 递归序列就像连锁反应：\n";
	outFile << "   每一项都依赖于前一项\n\n";

	outFile << "2. 递归计算很慢：\n";
	outFile << "   您必须按顺序计算每一项\n\n";

	outFile << "3. 寻找规律可以揭示捷径：\n";
	outFile << "   计算几项并寻找规律\n\n";

	outFile << "4. 闭式公式是即时的：\n";
	outFile << "   直接跳到任意项，无需中间步骤\n\n";

	outFile << "5. 对于这个问题：\n";
	outFile << "   原始: a(1) = 4, a(n+1) = (4*a(n) - 1)/(a(n) + 2)\n";
	outFile << "   捷径: a(n) = (n + 3) / n\n\n";

	outFile << "================================================================\n";
	outFile << "使用说明\n";
	outFile << "================================================================\n\n";

	outFile << "公式：a(n) = (n + 3) / n\n\n";

	outFile << "示例计算：\n\n";

	outFile << "例1：求 a(5)\n";
	outFile << "  a(5) = (5 + 3) / 5\n";
	outFile << "       = 8 / 5\n";
	outFile << "       = 1.6\n\n";

	outFile << "例2：求 a(100)\n";
	outFile << "  a(100) = (100 + 3) / 100\n";
	outFile << "         = 103 / 100\n";
	outFile << "         = 1.03\n\n";

	outFile << "例3：求 a(985)\n";
	outFile << "  a(985) = (985 + 3) / 985\n";
	outFile << "         = 988 / 985\n";
	outFile << "         ≈ 1.003045685\n\n";

	outFile << "================================================================\n";
	outFile << "关键要点\n";
	outFile << "================================================================\n\n";

	outFile << "• 递归方法：慢，需要计算所有前面的项\n";
	outFile << "• 闭式公式：快，可以直接计算任意项\n";
	outFile << "• 寻找规律是解决递归序列的关键\n";
	outFile << "• 当 n 趋向无穷大时，a(n) 趋向于 1\n\n";

	outFile << "================================================================\n";
	outFile << "程序结束 - 感谢使用！\n";
	outFile << "================================================================\n\n";

	outFile << "本文件由递归序列求解器自动生成\n";
	outFile << "Educational Recursive Sequence Solver\n";
	outFile << "版权所有 © 2025\n";

	outFile.close();

	cout << "\n================================================================\n";
	cout << "Chinese translation saved successfully!\n";
	cout << "================================================================\n";
	cout << "File: 递归序列求解器_简体中文版.txt\n";
	cout << "Location: Current project folder\n";
	cout << "Encoding: UTF-8 with BOM (opens correctly in Notepad/Word)\n\n";
	cout << "Your Chinese-speaking team members can now read the complete\n";
	cout << "tutorial in Simplified Chinese!\n";
	cout << "================================================================\n\n";
}