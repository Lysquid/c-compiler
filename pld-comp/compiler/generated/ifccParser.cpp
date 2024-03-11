
// Generated from ifcc.g4 by ANTLR 4.7.2


#include "ifccVisitor.h"

#include "ifccParser.h"


using namespace antlrcpp;
using namespace antlr4;

ifccParser::ifccParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ifccParser::~ifccParser() {
  delete _interpreter;
}

std::string ifccParser::getGrammarFileName() const {
  return "ifcc.g4";
}

const std::vector<std::string>& ifccParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ifccParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- AxiomContext ------------------------------------------------------------------

ifccParser::AxiomContext::AxiomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::ProgContext* ifccParser::AxiomContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}

tree::TerminalNode* ifccParser::AxiomContext::EOF() {
  return getToken(ifccParser::EOF, 0);
}


size_t ifccParser::AxiomContext::getRuleIndex() const {
  return ifccParser::RuleAxiom;
}

antlrcpp::Any ifccParser::AxiomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAxiom(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AxiomContext* ifccParser::axiom() {
  AxiomContext *_localctx = _tracker.createInstance<AxiomContext>(_ctx, getState());
  enterRule(_localctx, 0, ifccParser::RuleAxiom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    prog();
    setState(13);
    match(ifccParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgContext ------------------------------------------------------------------

ifccParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::ProgContext::INT() {
  return getToken(ifccParser::INT, 0);
}

ifccParser::StatementsContext* ifccParser::ProgContext::statements() {
  return getRuleContext<ifccParser::StatementsContext>(0);
}

ifccParser::Return_stmtContext* ifccParser::ProgContext::return_stmt() {
  return getRuleContext<ifccParser::Return_stmtContext>(0);
}


size_t ifccParser::ProgContext::getRuleIndex() const {
  return ifccParser::RuleProg;
}

antlrcpp::Any ifccParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ProgContext* ifccParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 2, ifccParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(15);
    match(ifccParser::INT);
    setState(16);
    match(ifccParser::T__0);
    setState(17);
    match(ifccParser::T__1);
    setState(18);
    match(ifccParser::T__2);
    setState(19);
    match(ifccParser::T__3);
    setState(20);
    statements();
    setState(21);
    return_stmt();
    setState(22);
    match(ifccParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

ifccParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ifccParser::StatementContext *> ifccParser::StatementsContext::statement() {
  return getRuleContexts<ifccParser::StatementContext>();
}

ifccParser::StatementContext* ifccParser::StatementsContext::statement(size_t i) {
  return getRuleContext<ifccParser::StatementContext>(i);
}


size_t ifccParser::StatementsContext::getRuleIndex() const {
  return ifccParser::RuleStatements;
}

antlrcpp::Any ifccParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::StatementsContext* ifccParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 4, ifccParser::RuleStatements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::INT

    || _la == ifccParser::VAR) {
      setState(24);
      statement();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

ifccParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::StatementContext::getRuleIndex() const {
  return ifccParser::RuleStatement;
}

void ifccParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DeclarationStatementContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::DeclarationStatementContext::INT() {
  return getToken(ifccParser::INT, 0);
}

std::vector<tree::TerminalNode *> ifccParser::DeclarationStatementContext::VAR() {
  return getTokens(ifccParser::VAR);
}

tree::TerminalNode* ifccParser::DeclarationStatementContext::VAR(size_t i) {
  return getToken(ifccParser::VAR, i);
}

ifccParser::DeclarationStatementContext::DeclarationStatementContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::DeclarationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitDeclarationStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignementStatementContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::AssignementStatementContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

ifccParser::ExprContext* ifccParser::AssignementStatementContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::AssignementStatementContext::AssignementStatementContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::AssignementStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAssignementStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefinitionStatementContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::DefinitionStatementContext::INT() {
  return getToken(ifccParser::INT, 0);
}

tree::TerminalNode* ifccParser::DefinitionStatementContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

ifccParser::ExprContext* ifccParser::DefinitionStatementContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::DefinitionStatementContext::DefinitionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::DefinitionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitDefinitionStatement(this);
  else
    return visitor->visitChildren(this);
}
ifccParser::StatementContext* ifccParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, ifccParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(51);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ifccParser::DeclarationStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(30);
      match(ifccParser::INT);
      setState(31);
      match(ifccParser::VAR);
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ifccParser::T__5) {
        setState(32);
        match(ifccParser::T__5);
        setState(33);
        match(ifccParser::VAR);
        setState(38);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(39);
      match(ifccParser::T__6);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ifccParser::DefinitionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(40);
      match(ifccParser::INT);
      setState(41);
      match(ifccParser::VAR);
      setState(42);
      match(ifccParser::T__7);
      setState(43);
      expr(0);
      setState(44);
      match(ifccParser::T__6);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ifccParser::AssignementStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(46);
      match(ifccParser::VAR);
      setState(47);
      match(ifccParser::T__7);
      setState(48);
      expr(0);
      setState(49);
      match(ifccParser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ifccParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::ExprContext::getRuleIndex() const {
  return ifccParser::RuleExpr;
}

void ifccParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::ParContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::ParContext::ParContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ParContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitPar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::VarExprContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

ifccParser::VarExprContext::VarExprContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::VarExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Mult_divContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::Mult_divContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::Mult_divContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

tree::TerminalNode* ifccParser::Mult_divContext::MULT_DIV() {
  return getToken(ifccParser::MULT_DIV, 0);
}

ifccParser::Mult_divContext::Mult_divContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::Mult_divContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMult_div(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SignExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::SignExprContext::ADD_SUB() {
  return getToken(ifccParser::ADD_SUB, 0);
}

ifccParser::ExprContext* ifccParser::SignExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::SignExprContext::SignExprContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::SignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitSignExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Add_subContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::Add_subContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::Add_subContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

tree::TerminalNode* ifccParser::Add_subContext::ADD_SUB() {
  return getToken(ifccParser::ADD_SUB, 0);
}

ifccParser::Add_subContext::Add_subContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::Add_subContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAdd_sub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ConstExprContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}

ifccParser::ConstExprContext::ConstExprContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitConstExpr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ExprContext* ifccParser::expr() {
   return expr(0);
}

ifccParser::ExprContext* ifccParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ifccParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ifccParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, ifccParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(62);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::ADD_SUB: {
        _localctx = _tracker.createInstance<SignExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(54);
        match(ifccParser::ADD_SUB);
        setState(55);
        expr(6);
        break;
      }

      case ifccParser::CONST: {
        _localctx = _tracker.createInstance<ConstExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(56);
        match(ifccParser::CONST);
        break;
      }

      case ifccParser::VAR: {
        _localctx = _tracker.createInstance<VarExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(57);
        match(ifccParser::VAR);
        break;
      }

      case ifccParser::T__1: {
        _localctx = _tracker.createInstance<ParContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(58);
        match(ifccParser::T__1);
        setState(59);
        expr(0);
        setState(60);
        match(ifccParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(72);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(70);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<Mult_divContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(64);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(65);
          match(ifccParser::MULT_DIV);
          setState(66);
          expr(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<Add_subContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(67);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(68);
          match(ifccParser::ADD_SUB);
          setState(69);
          expr(5);
          break;
        }

        } 
      }
      setState(74);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Return_stmtContext ------------------------------------------------------------------

ifccParser::Return_stmtContext::Return_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::Return_stmtContext::RETURN() {
  return getToken(ifccParser::RETURN, 0);
}

ifccParser::ExprContext* ifccParser::Return_stmtContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::Return_stmtContext::getRuleIndex() const {
  return ifccParser::RuleReturn_stmt;
}

antlrcpp::Any ifccParser::Return_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitReturn_stmt(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Return_stmtContext* ifccParser::return_stmt() {
  Return_stmtContext *_localctx = _tracker.createInstance<Return_stmtContext>(_ctx, getState());
  enterRule(_localctx, 10, ifccParser::RuleReturn_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(ifccParser::RETURN);
    setState(76);
    expr(0);
    setState(77);
    match(ifccParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool ifccParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 4: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ifccParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ifccParser::_decisionToDFA;
atn::PredictionContextCache ifccParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ifccParser::_atn;
std::vector<uint16_t> ifccParser::_serializedATN;

std::vector<std::string> ifccParser::_ruleNames = {
  "axiom", "prog", "statements", "statement", "expr", "return_stmt"
};

std::vector<std::string> ifccParser::_literalNames = {
  "", "'main'", "'('", "')'", "'{'", "'}'", "','", "';'", "'='", "'return'", 
  "", "'int'"
};

std::vector<std::string> ifccParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "RETURN", "CONST", "INT", "VAR", "ADD_SUB", 
  "MULT_DIV", "COMMENT", "DIRECTIVE", "WS"
};

dfa::Vocabulary ifccParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ifccParser::_tokenNames;

ifccParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x13, 0x52, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x7, 0x4, 0x1c, 
    0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x1f, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x7, 0x5, 0x25, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x28, 0xb, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x36, 
    0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x41, 0xa, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x49, 0xa, 0x6, 
    0xc, 0x6, 0xe, 0x6, 0x4c, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x2, 0x3, 0xa, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 
    0x2, 0x2, 0x54, 0x2, 0xe, 0x3, 0x2, 0x2, 0x2, 0x4, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x8, 0x35, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x40, 0x3, 0x2, 0x2, 0x2, 0xc, 0x4d, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 0x5, 
    0x4, 0x3, 0x2, 0xf, 0x10, 0x7, 0x2, 0x2, 0x3, 0x10, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x11, 0x12, 0x7, 0xd, 0x2, 0x2, 0x12, 0x13, 0x7, 0x3, 0x2, 0x2, 
    0x13, 0x14, 0x7, 0x4, 0x2, 0x2, 0x14, 0x15, 0x7, 0x5, 0x2, 0x2, 0x15, 
    0x16, 0x7, 0x6, 0x2, 0x2, 0x16, 0x17, 0x5, 0x6, 0x4, 0x2, 0x17, 0x18, 
    0x5, 0xc, 0x7, 0x2, 0x18, 0x19, 0x7, 0x7, 0x2, 0x2, 0x19, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x1c, 0x5, 0x8, 0x5, 0x2, 0x1b, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0xd, 0x2, 0x2, 0x21, 
    0x26, 0x7, 0xe, 0x2, 0x2, 0x22, 0x23, 0x7, 0x8, 0x2, 0x2, 0x23, 0x25, 
    0x7, 0xe, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x25, 0x28, 0x3, 
    0x2, 0x2, 0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x3, 0x2, 
    0x2, 0x2, 0x27, 0x29, 0x3, 0x2, 0x2, 0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 
    0x2, 0x29, 0x36, 0x7, 0x9, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0xd, 0x2, 0x2, 
    0x2b, 0x2c, 0x7, 0xe, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0xa, 0x2, 0x2, 0x2d, 
    0x2e, 0x5, 0xa, 0x6, 0x2, 0x2e, 0x2f, 0x7, 0x9, 0x2, 0x2, 0x2f, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0xe, 0x2, 0x2, 0x31, 0x32, 0x7, 
    0xa, 0x2, 0x2, 0x32, 0x33, 0x5, 0xa, 0x6, 0x2, 0x33, 0x34, 0x7, 0x9, 
    0x2, 0x2, 0x34, 0x36, 0x3, 0x2, 0x2, 0x2, 0x35, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x35, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x35, 0x30, 0x3, 0x2, 0x2, 0x2, 
    0x36, 0x9, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x8, 0x6, 0x1, 0x2, 0x38, 
    0x39, 0x7, 0xf, 0x2, 0x2, 0x39, 0x41, 0x5, 0xa, 0x6, 0x8, 0x3a, 0x41, 
    0x7, 0xc, 0x2, 0x2, 0x3b, 0x41, 0x7, 0xe, 0x2, 0x2, 0x3c, 0x3d, 0x7, 
    0x4, 0x2, 0x2, 0x3d, 0x3e, 0x5, 0xa, 0x6, 0x2, 0x3e, 0x3f, 0x7, 0x5, 
    0x2, 0x2, 0x3f, 0x41, 0x3, 0x2, 0x2, 0x2, 0x40, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x40, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x41, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x42, 
    0x43, 0xc, 0x7, 0x2, 0x2, 0x43, 0x44, 0x7, 0x10, 0x2, 0x2, 0x44, 0x49, 
    0x5, 0xa, 0x6, 0x8, 0x45, 0x46, 0xc, 0x6, 0x2, 0x2, 0x46, 0x47, 0x7, 
    0xf, 0x2, 0x2, 0x47, 0x49, 0x5, 0xa, 0x6, 0x7, 0x48, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0x48, 0x45, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4c, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x4b, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4d, 
    0x4e, 0x7, 0xb, 0x2, 0x2, 0x4e, 0x4f, 0x5, 0xa, 0x6, 0x2, 0x4f, 0x50, 
    0x7, 0x9, 0x2, 0x2, 0x50, 0xd, 0x3, 0x2, 0x2, 0x2, 0x8, 0x1d, 0x26, 
    0x35, 0x40, 0x48, 0x4a, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ifccParser::Initializer ifccParser::_init;
