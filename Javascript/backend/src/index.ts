import Fastify from 'fastify';

const fastify = Fastify({logger: true});

fastify.get('/', async () => {
    return {message: 'Hello Backend!'};
});

fastify.listen({port: 3001});
