// Generated from ifcc.g4 by ANTLR 4.7.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ifccParser}.
 */
public interface ifccListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ifccParser#axiom}.
	 * @param ctx the parse tree
	 */
	void enterAxiom(ifccParser.AxiomContext ctx);
	/**
	 * Exit a parse tree produced by {@link ifccParser#axiom}.
	 * @param ctx the parse tree
	 */
	void exitAxiom(ifccParser.AxiomContext ctx);
	/**
	 * Enter a parse tree produced by {@link ifccParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(ifccParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link ifccParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(ifccParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link ifccParser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStatements(ifccParser.StatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link ifccParser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStatements(ifccParser.StatementsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code declarationStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationStatement(ifccParser.DeclarationStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code declarationStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationStatement(ifccParser.DeclarationStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code definitionStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterDefinitionStatement(ifccParser.DefinitionStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code definitionStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitDefinitionStatement(ifccParser.DefinitionStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code assignementStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterAssignementStatement(ifccParser.AssignementStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code assignementStatement}
	 * labeled alternative in {@link ifccParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitAssignementStatement(ifccParser.AssignementStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code par}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterPar(ifccParser.ParContext ctx);
	/**
	 * Exit a parse tree produced by the {@code par}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitPar(ifccParser.ParContext ctx);
	/**
	 * Enter a parse tree produced by the {@code varExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterVarExpr(ifccParser.VarExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code varExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitVarExpr(ifccParser.VarExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mult_div}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterMult_div(ifccParser.Mult_divContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mult_div}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitMult_div(ifccParser.Mult_divContext ctx);
	/**
	 * Enter a parse tree produced by the {@code signExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterSignExpr(ifccParser.SignExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code signExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitSignExpr(ifccParser.SignExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code add_sub}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterAdd_sub(ifccParser.Add_subContext ctx);
	/**
	 * Exit a parse tree produced by the {@code add_sub}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitAdd_sub(ifccParser.Add_subContext ctx);
	/**
	 * Enter a parse tree produced by the {@code constExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterConstExpr(ifccParser.ConstExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code constExpr}
	 * labeled alternative in {@link ifccParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitConstExpr(ifccParser.ConstExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ifccParser#return_stmt}.
	 * @param ctx the parse tree
	 */
	void enterReturn_stmt(ifccParser.Return_stmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link ifccParser#return_stmt}.
	 * @param ctx the parse tree
	 */
	void exitReturn_stmt(ifccParser.Return_stmtContext ctx);
}