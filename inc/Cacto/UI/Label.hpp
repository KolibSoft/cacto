#ifndef CACTO_LABEL_HPP
#define CACTO_LABEL_HPP

#include <Cacto/UI/Span.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    class CACTO_UI_API Label
        : public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        const Block& getBlock() const;
        Block& getBlock();

        const Span& getSpan() const;
        Span& getSpan();

        Label();
        virtual ~Label();

    private:
        FrameLayout m_frame;
        Span m_span;
    };

}

#endif